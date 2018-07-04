#pragma once
#pragma execution_character_set("utf-8")

#include "PanelView.h"
#include <QUrl>
#include <QMediaPlayer>
#include <QVideoWidget> 
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QFileInfo>
#include <QGroupBox>

void PanelView::open_media_slot(const QString& path){
	if (path.size()){
		__player__->stop();
		__player__->setMedia(QUrl::fromLocalFile(path));
		__player__->play();
		__player__->pause();
		__playButton__->setDisabled(false);
		__embShowButton__->setDisabled(false);
		__extShowButton__->setDisabled(false);
		QFileInfo qfinfo(path);
		this->setWindowTitle("视频信息隐藏系统 -- " + qfinfo.fileName());
	}
	else{
		__playButton__->setDisabled(true);
		__embShowButton__->setDisabled(true);
		__extShowButton__->setDisabled(true);
	}
}

void PanelView::play_slot(OperaStatus status){
	switch (status){
	case STOP:
		__player__->stop();
		break;
	case RUNNING:
		__player__->play();
		__playButton__->setText("暂停");
		break;
	case PAUSE:
		__player__->pause();
		__playButton__->setText("播放");
		break;
	}
}

void PanelView::open_emb_secert_slot(const QString& path){
	__embSecretEdit__->setText(path);
}

void PanelView::save_emb_media_slot(const QString& path){
	__embMediaEdit__->setText(path);
}

void PanelView::save_ext_secert_slot(const QString& path){
	__extSecretEdit__->setText(path);
}

void  PanelView::emb_progress_slot(int val){
	__embProgress__->setValue(val);
}

void  PanelView::ext_progress_slot(int val){
	__extProgress__->setValue(val);
}

void PanelView::start_slot(){
	__embButton__->setText("停止");
	__extButton__->setText("停止");
	__openEmbSecretButton__->setDisabled(true);
	__openEmbMediaButton__->setDisabled(true);
	__openExtSecretButton__->setDisabled(true);
	__embShowButton__->setDisabled(true);
	__extShowButton__->setDisabled(true);
	__openMediaButton__->setDisabled(true);
	__extSecretEdit__->setDisabled(true);
	__embMediaEdit__->setDisabled(true);
	__embSecretEdit__->setDisabled(true);
}

void PanelView::stop_slot(){
	__embButton__->setText("嵌入");
	__extButton__->setText("提取");
	__openEmbSecretButton__->setDisabled(false);
	__openEmbMediaButton__->setDisabled(false);
	__openExtSecretButton__->setDisabled(false);
	__embShowButton__->setDisabled(false);
	__extShowButton__->setDisabled(false);
	__openMediaButton__->setDisabled(false);
	__extSecretEdit__->setDisabled(false);
	__embMediaEdit__->setDisabled(false);
	__embSecretEdit__->setDisabled(false);
}

void  PanelView::algo_name_slot(const QString& algoName){
	__embWidget__->setTitle("嵌入算法:" + algoName);
	__extWidget__->setTitle("提取算法:" + algoName);
}