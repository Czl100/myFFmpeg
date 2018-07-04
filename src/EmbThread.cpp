#pragma once
#pragma execution_character_set("utf-8")

#include "EmbThread.h"
#include "empeg/Emedia.h"
#include "PanelStatusModel.h"
#include "AlgoConf.h"
#include <QDebug>
#include <QDir>
#include <QTextCodec>

using namespace std;

EmbThread::EmbThread(shared_ptr<PanelStatusModel> model){
	__mediaPath__ = model->media_path();
	__workspace__ = model->workspace();					//algorithms/三维低码率/workspace
	__exePath__ = model->exe_path();
	__type__ = ENCODE;
	__embMediaPath__ = model->emb_media_path();
	model->load_env_args(__env__, __args__);			//载入_env_和_args_;秘密文件的路径是在model中的
}

void EmbThread::run(){
	stopped = false;
	emit algoMessageSignal(ENCODE, "============ 信息隐藏 ============", 1);
	// 1).media->yuv转换
	shared_ptr<Emedia> media = Emedia::generate(__mediaPath__.toStdString());
	QString id = QString::number(qrand());
	QString yuvwhere = QDir::currentPath() + "/tmp/" + id + ".yuv";
	QString audiowhere = QDir::currentPath() + "/tmp/" + id + ".wma";
	QString videowhere = QDir::currentPath() + "/tmp/" + id + ".264";
	int high = media->high();
	int width = media->width();
	int frames = media->frames()-1;
	double fps = media->fps();
	emit algoMessageSignal(ENCODE, "开始提取音频文件...", 5);
	if (media->audio_exists()){
		media->xaudio(audiowhere.toStdString());
		if (stopped){ return; }
		emit algoMessageSignal(ENCODE, "【完成】音频文件提取", 10);
	}
	else{
		emit algoMessageSignal(ENCODE, "音频文件不存在", 10);
		if (stopped){ return; }
	}
	emit algoMessageSignal(ENCODE, "开始提取YUV...", 10);
	media->xyuv(yuvwhere.toStdString());
	emit algoMessageSignal(ENCODE, "【结束】YUV提取", 40);
	if (stopped){ return; }
	high = media->high();

	// 2).更新配置文件
	AlgoConf::encode_height(high);
	AlgoConf::encode_width(width);
	AlgoConf::encode_frames(frames);
	AlgoConf::encode_fps(fps);
	AlgoConf::input_file_path(ENCODE, yuvwhere);
	AlgoConf::output_file_path(ENCODE, videowhere);
	AlgoConf::sync(ENCODE);

	// 3).配置进程环境
	QProcess p;
	p.setWorkingDirectory(__workspace__);	//algorithms/三维低码率/workspace
	p.setEnvironment(__env__);
	qRegisterMetaType<QProcess::ProcessError>("QProcess::ProcessError");
	connect(&p, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processErrorSlot(QProcess::ProcessError)));

	QString strEnv;
	QString strCmd = __exePath__ + " ";		//algorithms/三维低码率/lencode.exe
	for (int i = 0; i < __env__.size(); i++){ strEnv.append(__env__[i] + ";"); }
	for (int i = 0; i < __args__.size(); i++){ strEnv.append(__args__[i] + " "); }
	qDebug() << QString("[Start]  cmd:%1; env:%2").arg(strCmd).arg(strEnv);

	// 4).进程开始
	emit algoMessageSignal(ENCODE, "开始运行嵌入算法进程...", 40);
	p.start(__exePath__, __args__);			// 进程开始执行
	p.waitForReadyRead();
	int cnt = 1;
	// 没有读取完，或者stop为false则一直读
	for (QByteArray line = p.readLine(); line.size() != 0 && (!stopped); line = p.readLine(), cnt++){
		cnt += 1;
		int progress = (cnt * 100.0 / (frames + 30)) / 2 + 40;
		emit algoMessageSignal(ENCODE, line, progress > 90 ? 90 : progress);		// 避免多次弹出完成对话框
		p.waitForReadyRead();
	}
 	if (stopped){
		p.terminate();			// 终止进程, 将会触发进程错误，由此来通知主线程进程结束。
	}
	else{						// 进程正常结束
		p.waitForFinished();
		int exitCode = p.exitCode();
		if (exitCode != 0){
			emit algoMessageSignal(ENCODE, "异常码:" + QString::number(exitCode) + ", 异常信息:" + p.readAllStandardError(), 100);
		}
		else{
			// 5). 将264和音频结合在一起
			emit algoMessageSignal(ENCODE, "【结束】嵌入完成", 90);
			emit algoMessageSignal(ENCODE, "开始封装多媒体文件...", 90);
			if (media->audio_exists()){
				Emedia::combine(__embMediaPath__.toStdString(), videowhere.toStdString(), audiowhere.toStdString());
			}
			else{
				Emedia::combine(__embMediaPath__.toStdString(), videowhere.toStdString());
			}
			emit algoMessageSignal(ENCODE, "【完成】多媒体文件封装", 99);
			emit algoMessageSignal(ENCODE, "信息隐藏完成", 100);
		}
	}
	__env__.clear();
	__args__.clear();
}