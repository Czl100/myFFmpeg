#pragma once
#pragma execution_character_set("utf-8")

#ifndef __PANEL_CONTROLLER_
#define __PANEL_CONTROLLER_

#include "IPanelController.h"
#include "VihThreadRunner.h"
#include "ConsoleWindow.h"

class PanelController : public IPanelController{
	Q_OBJECT
public:
	PanelController();
public slots :
	void open_algorithm_slot() override;
	void open_console_slot() override;

	void open_video_slot() override;
	void play_video_slot() override;
	void play_progress_slot() override;

	void open_emb_secert_slot() override;
	void save_emb_media_slot() override;
	void start_emb_slot() override;

	void save_ext_secert_slot() override;
	void start_ext_slot() override;

	void emb_media_change_slot(const QString& line) override;
	void ext_secret_change_slot(const QString& line) override;
	void emb_secret_change_slot(const QString& line) override;
	

	void runnerSlot(int exitCode, const QString &line, int val);

private:
	VihThreadRunner __runner__;
	ConsoleWindow __consoleWindow__;
};

#endif