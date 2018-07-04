#pragma once
#pragma execution_character_set("utf-8")

#ifndef __INTERFACE_PANEL_VIEW_
#define __INTERFACE_PANEL_VIEW_

#include <QObject>
#include <QtWidgets/QMainWindow>
#include "defines.h"

class IPanelController;
class QString;

// 提供视图接口
class BasePanelView{
public:
	virtual ~BasePanelView(){}
	virtual void link_controller(const IPanelController &controller) = 0;
};

// 提供视图接口 以及 视图信号
class IPanelView : public QMainWindow, public BasePanelView{
	Q_OBJECT

public:
	IPanelView(QWidget *parent = nullptr) :QMainWindow(parent){}

public slots :
	virtual void open_media_slot(const QString& mediaPath) = 0;
	virtual void play_slot(OperaStatus status) = 0;
	virtual void open_emb_secert_slot(const QString& path) = 0;
	virtual void save_emb_media_slot(const QString& path) = 0;
	virtual void save_ext_secert_slot(const QString& path) = 0;
	virtual void emb_progress_slot(int val) = 0;
	virtual void ext_progress_slot(int val) = 0;
	virtual void algo_name_slot(const QString& algoName) = 0;
	virtual void start_slot() = 0;
	virtual void stop_slot() = 0;
};

#endif