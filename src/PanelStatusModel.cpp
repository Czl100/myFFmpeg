#pragma once
#pragma execution_character_set("utf-8")

#include "PanelStatusModel.h"
#include "IPanelView.h"
#include "AlgoConf.h"
#include <QList>

void PanelStatusModel::set_view(std::shared_ptr<IPanelView> v){
	connect(this, SIGNAL(open_media_signal(const QString&)), v.get(), SLOT(open_media_slot(const QString&)));
	connect(this, SIGNAL(play_signal(OperaStatus)), v.get(), SLOT(play_slot(OperaStatus)));
	connect(this, SIGNAL(open_emb_secret_signal(const QString&)), v.get(), SLOT(open_emb_secert_slot(const QString&)));
	connect(this, SIGNAL(save_emb_media_signal(const QString&)), v.get(), SLOT(save_emb_media_slot(const QString&)));

	connect(this, SIGNAL(save_ext_secret_signal(const QString&)), v.get(), SLOT(save_ext_secert_slot(const QString&)));
	connect(this, SIGNAL(emb_progress_signal(int)), v.get(), SLOT(emb_progress_slot(int)));
	connect(this, SIGNAL(ext_progress_signal(int)), v.get(), SLOT(ext_progress_slot(int)));
	connect(this, SIGNAL(start_signal()), v.get(), SLOT(start_slot()));
	connect(this, SIGNAL(stop_signal()), v.get(), SLOT(stop_slot()));
	connect(this, SIGNAL(algo_name_signal(const QString&)), v.get(), SLOT(algo_name_slot(const QString&)));
	// 根据model的当前状态，渲染view
	emit open_media_signal(__mediaPath__);		// __mediaPath__长度为0时，view将会认为文件不可用，置灰按钮。
	emit algo_name_signal(algo_name());
}

// ================================ 读取数据 ================================
const QString& PanelStatusModel::media_path(){
	return __mediaPath__;
}
OperaStatus PanelStatusModel::play_status() {
	return __playStatus__;
}

const QString& PanelStatusModel::emb_secret_path(){
	return __embSecretPath__;
}

const QString& PanelStatusModel::emb_media_path(){
	return __embMediaPath__;
}

const QString& PanelStatusModel::ext_secret_path(){
	return __extSecretPath__;
}

// ================================ 写入数据 ================================
void PanelStatusModel::media_path(const QString& path){
	// 路径不同则重新打开媒体
	if (__mediaPath__.compare(path)){
		__mediaPath__ = path;
		emit open_media_signal(__mediaPath__);
		__playStatus__ = PAUSE;
	}
}

void PanelStatusModel::play_status(OperaStatus status) {
	if (__playStatus__ != status){
		__playStatus__ = status;
		emit play_signal(__playStatus__);
	}
}

void PanelStatusModel::emb_secret_path(const QString& secertPath, bool sync){
	// 路径不同则重新打开
	if (__embSecretPath__.compare(secertPath)){
		__embSecretPath__ = secertPath;
		AlgoConf::emb_secret_path(__embSecretPath__);
		if (sync){
			emit open_emb_secret_signal(__embSecretPath__);
		}
	}
}

void PanelStatusModel::emb_media_path(const QString& path, bool sync){
	// 路径不同则重新打开
	if (__embMediaPath__.compare(path)){
		__embMediaPath__ = path;
		if (sync){
			emit save_emb_media_signal(__embMediaPath__);
		}
	}
}

void PanelStatusModel::ext_secret_path(const QString& path, bool sync){
	if (__extSecretPath__.compare(path)){
		__extSecretPath__ = path;
		AlgoConf::ext_secret_path(__extSecretPath__);
		if (sync){
			emit save_ext_secret_signal(__extSecretPath__);
		}
	}
}

void PanelStatusModel::emb_progress(int val){
	emit emb_progress_signal(val);
}

void PanelStatusModel::ext_progress(int val){
	emit ext_progress_signal(val);
}

void PanelStatusModel::start(){
	emit start_signal();
}

void PanelStatusModel::stop(){
	emit stop_signal();
}

void PanelStatusModel::set_algo_idx(int idx){
	algo_idx(idx);
	emit algo_name_signal(algo_name());
}

void PanelStatusModel::wrong(){
	__wrong__ = true;
}