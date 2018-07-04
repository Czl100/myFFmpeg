#pragma once
#pragma execution_character_set("utf-8")

#include "ExtThread.h"
#include "empeg/Emedia.h"
#include "PanelStatusModel.h"
#include "AlgoConf.h"
#include <QDebug>
#include <QDir>
#include "utils.h"

using namespace std;

ExtThread::ExtThread(std::shared_ptr<PanelStatusModel> model){
	__mediaPath__ = model->media_path();
	__workspace__ = model->workspace();
	__exePath__ = model->exe_path();
	__type__ = DECODE;
	model->load_env_args(__env__, __args__);			// 秘密文件的路径是在model中的
}

void ExtThread::run(){
	stopped = false;
	emit algoMessageSignal(DECODE, "============ 信息提取 ============", 1);
	// 1).提取264
	QString id = QString::number(qrand());
	shared_ptr<Emedia> media = Emedia::generate(__mediaPath__.toStdString());
	int frames = media->frames();
	QString videowhere = QDir::currentPath() + "/tmp/" + id + ".264";
	QString yuvwhere = QDir::currentPath() + "/tmp/" + id + ".yuv";
	emit algoMessageSignal(DECODE, "读取多媒体中的视频文件...", 5);
	media->xvideo(videowhere.toStdString());
	if (stopped){ return; }

	// 2).更新配置文件
	AlgoConf::input_file_path(DECODE, videowhere);
	AlgoConf::output_file_path(DECODE, yuvwhere);
	AlgoConf::sync(DECODE);

	// 3).配置进程环境
	QProcess p;
	p.setWorkingDirectory(__workspace__);
	p.setEnvironment(__env__);
	qRegisterMetaType<QProcess::ProcessError>("QProcess::ProcessError");
	connect(&p, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processErrorSlot(QProcess::ProcessError)));

	QString strEnv;
	QString strCmd = __exePath__ + " ";
	for (int i = 0; i < __env__.size(); i++){ strEnv.append(__env__[i] + ";"); }
	for (int i = 0; i < __args__.size(); i++){ strEnv.append(__args__[i] + " "); }
	qDebug() << QString("[Start]  cmd:%1; env:%2").arg(strCmd).arg(strEnv);

	// 4).提取秘密数据进程
	emit algoMessageSignal(DECODE, "开始运行提取进程...", 50);
	p.start(__exePath__, __args__);			// 进程开始执行
	p.waitForReadyRead();
	int cnt = 1;
	// 没有读取完，或者stop为false则一直读
	for (QByteArray line = p.readLine(); line.size() != 0 && (!stopped); line = p.readLine(), cnt++){
		cnt += 1;
		int progress = (cnt * 100.0 / (frames + 10)) / 2 + 50;
		emit algoMessageSignal(DECODE, line, progress > 99 ? 99 : progress);		// 避免多次弹出完成对话框
		p.waitForReadyRead();
	}
	if (stopped){
		p.terminate();			// 终止进程, 将会触发进程错误，由此来通知主线程进程结束。
	}
	else{						// 进程正常结束
		p.waitForFinished();
		int exitCode = p.exitCode();
		if (exitCode != 0){
			emit algoMessageSignal(DECODE, "异常码:" + QString::number(exitCode) + ", 异常信息:" + p.readAllStandardError(), 100);
		}
		else{
			emit algoMessageSignal(DECODE, "提取信息完成", 100);
		}
	}
	__env__.clear();
	__args__.clear();
}