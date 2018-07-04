#pragma once
#pragma execution_character_set("utf-8")

#ifndef __PANEL_STATUS_MODEL_H
#define __PANEL_STATUS_MODEL_H

#include <QObject>
#include <memory>
#include <QList>
#include "AlgosModel.h"
#include "defines.h"

class QString;
class IPanelView;
class Algorithm;

class PanelStatusModel : public QObject, public AlgosModel{

	Q_OBJECT

// 发送的信号
signals :
	void open_media_signal(const QString& path);
	void play_signal(OperaStatus status);
	void open_emb_secret_signal(const QString& path);
	void save_emb_media_signal(const QString& path);
	void save_ext_secret_signal(const QString& path);
	void emb_progress_signal(int val);
	void ext_progress_signal(int val);
	void algo_name_signal(const QString& algo_name);
	void start_signal();
	void stop_signal();

// 初始化
public:
	PanelStatusModel() :__mediaPath__(""), __playStatus__(STOP), __wrong__(false){}

// 将信号和view的slots连接
public:
	void set_view(std::shared_ptr<IPanelView> v);

// 写函数
public:
	void media_path(const QString& path);
	void play_status(OperaStatus status);
	void emb_secret_path(const QString& path, bool sync = true);
	void emb_media_path(const QString& path, bool sync = true);
	void ext_secret_path(const QString& path, bool sync = true);
	void emb_progress(int val);
	void ext_progress(int val);
	void set_algo_idx(int idx);
	void start();
	void stop();
	void wrong();

// 读函数
public:
	const QString& media_path();
	OperaStatus play_status();
	const QString& emb_secret_path();
	const QString& emb_media_path();
	const QString& ext_secret_path();

private:
	QString __mediaPath__;
	QString __embSecretPath__;
	QString __embMediaPath__;
	QString __extSecretPath__;
	OperaStatus __playStatus__;
	bool __wrong__;


};

#endif