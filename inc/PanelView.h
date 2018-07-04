#pragma once
#pragma execution_character_set("utf-8")

#ifndef __PANEL_VIEW_H
#define __PANEL_VIEW_H

#include "IPanelView.h"
#include <QString>

class QMediaPlayer;
class QPushButton;
class IPanelController;
class QProgressBar;
class QLineEdit;
class QAction;
class QGroupBox;
class QLabel;

class PanelView : public IPanelView{
	Q_OBJECT
public:
	PanelView(QWidget *parent = nullptr);

public slots :
	void open_media_slot(const QString& mediaPath) override;
	void play_slot(OperaStatus status) override;
	void open_emb_secert_slot(const QString& mediaPath) override;
	void save_emb_media_slot(const QString& path) override;

	void save_ext_secert_slot(const QString& path) override;

	void emb_progress_slot(int val) override;
	void ext_progress_slot(int val) override;
	void algo_name_slot(const QString& algoName) override;
	void start_slot() override ;
	void stop_slot() override ;

	void link_controller(const IPanelController &controller) override;

private:
	void __init_layout__();

private:
	QAction * __openAlgorithmAction__;
	QAction * __openConsoleAction__;
	QMediaPlayer* __player__;
	QPushButton* __playButton__;
	QPushButton* __openMediaButton__;
	QPushButton* __embShowButton__;
	QPushButton* __extShowButton__;

	QPushButton* __embButton__;
	QProgressBar* __embProgress__;
	QGroupBox* __embWidget__;
	QLineEdit* __embSecretEdit__;
	QLineEdit* __embMediaEdit__; 
	QPushButton* __openEmbSecretButton__;
	QPushButton* __openEmbMediaButton__;

	QPushButton* __extButton__;
	QGroupBox* __extWidget__;
	QProgressBar* __extProgress__;
	QLineEdit* __extSecretEdit__;
	QPushButton* __openExtSecretButton__;
};


#endif