#pragma once
#pragma execution_character_set("utf-8")

#include "PanelController.h"
#include "IPanelView.h"
#include "PanelStatusModel.h"
#include <QFileDialog>
#include <QUrl>
#include "OpenAlgorithmsDialog.h"
#include "EmbThread.h"
#include "ExtThread.h"
#include <QMessageBox>
#include <QFile>

using namespace std;

PanelController::PanelController(){
	connect(&__runner__, SIGNAL(runnerSignal(int, const QString&, int)), this, SLOT(runnerSlot(int, const QString&, int)));
}

void PanelController::open_video_slot(){
	QString path = QFileDialog::getOpenFileName(nullptr, "选择多媒体文件", ".", "*.*");
	if (path.size() == 0){
		return;
	}
	__statusModel__->media_path(path);

}

void PanelController::play_video_slot(){
	OperaStatus status = __statusModel__->play_status();
	switch (status){
	case PAUSE:
		__statusModel__->play_status(RUNNING);
		break;
	case RUNNING:
		__statusModel__->play_status(PAUSE);
		break;
	}
}

void PanelController::play_progress_slot(){

}

void PanelController::open_algorithm_slot(){
	OpenAlgorithmsDialog dialog = OpenAlgorithmsDialog(__statusModel__->algo_idx(), __statusModel__->algos_list());
	dialog.exec();
	int newidx = dialog.retval();
	__statusModel__->set_algo_idx(newidx);
}

void PanelController::open_console_slot(){
	__consoleWindow__.show();
}

void PanelController::open_emb_secert_slot() {
	QString path = QFileDialog::getOpenFileName(nullptr, "选择秘密文件", ".");
	if (path.size() == 0){
		return;
	}
	__statusModel__->emb_secret_path(path);
}

void PanelController::save_emb_media_slot(){
	QString path = QFileDialog::getSaveFileName(nullptr, "载密视频保存路径");
	if (path.size() == 0){
		return;
	}
	__statusModel__->emb_media_path(path);
}

void PanelController::start_emb_slot(){
	if (__runner__.status() == STOP){
		if (__statusModel__->emb_secret_path().size() == 0){
			QMessageBox::critical(nullptr, "视频信息隐藏系统", "没有选择秘密文件", QMessageBox::Yes);
			return;
		}
		if (__statusModel__->emb_media_path().size() == 0){
			QMessageBox::critical(nullptr, "视频信息隐藏系统", "没有载密文件输出", QMessageBox::Yes);
			return;
		}
		if (QMessageBox::information(nullptr, "视频信息隐藏系统", "开始信息隐藏", QMessageBox::Yes | QMessageBox::No)
			== QMessageBox::No){
			return;
		}
		__statusModel__->opera_type(ENCODE);
		__statusModel__->start();
		if (__runner__.start(shared_ptr<VihThread>(new EmbThread(__statusModel__)))){

		}
		else{		// 运行失败

		}
	}
	else{
		if (QMessageBox::information(nullptr, "视频信息隐藏系统", "正在隐藏，是否停止？", QMessageBox::Yes | QMessageBox::No)
			== QMessageBox::No){
			return;
		}
		__runner__.stop();
	}
}

void PanelController::save_ext_secert_slot(){
	QString path = QFileDialog::getSaveFileName(nullptr, "选择秘密文件保存路径", ".");
	if (path.size() == 0){
		return;
	}
	__statusModel__->ext_secret_path(path);
}

void PanelController::start_ext_slot() {
	if(__runner__.status() == STOP){
		if (__statusModel__->ext_secret_path().size() == 0){
			QMessageBox::critical(nullptr, "视频信息隐藏系统", "没有选择秘密文件输出路径", QMessageBox::Yes);
			return;
		}
		if (QMessageBox::information(nullptr, "视频信息隐藏系统", "开始信息提取", QMessageBox::Yes | QMessageBox::No)
			== QMessageBox::No){
			return;
		}
		__statusModel__->opera_type(DECODE);
		__statusModel__->start();
		if (__runner__.start(shared_ptr<VihThread>(new ExtThread(__statusModel__)))){

		}
		else{		// 运行失败

		}
	}
	else{
		if (QMessageBox::information(nullptr, "视频信息隐藏系统", "正在提取，是否停止？", QMessageBox::Yes | QMessageBox::No)
			== QMessageBox::No){
			return;
		}
		__runner__.stop();
	}
	
}

void PanelController::runnerSlot(int type, const QString &line, int val){
	if (type == ENCODE){
		__statusModel__->emb_progress(val);
	}
	else if (type == DECODE){
		__statusModel__->ext_progress(val);
	}
	else{
		__statusModel__->emb_progress(val);
		__statusModel__->ext_progress(val);
	}
	if (!__consoleWindow__.isHidden()){
		__consoleWindow__.append(line);
	}
	if (val == 100){
		QMessageBox::information(nullptr, "视频信息隐藏系统", line, QMessageBox::Yes);
		__statusModel__->stop();
	}
}

void PanelController::ext_secret_change_slot(const QString& line){
	__statusModel__->ext_secret_path(line, false);
}

void PanelController::emb_secret_change_slot(const QString& line){
	__statusModel__->emb_secret_path(line, false);
}

void PanelController::emb_media_change_slot(const QString& line) {
	__statusModel__->emb_media_path(line, false);
}