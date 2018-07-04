#pragma once
#pragma execution_character_set("utf-8")

#ifndef __EXT_THREAD_H
#define __EXT_THREAD_H

#include "VihThread.h"
#include <memory>

class ExtThread : public VihThread{
	Q_OBJECT
public:
	ExtThread(std::shared_ptr<PanelStatusModel> model);
	~ExtThread(){}

protected:
	void run() override;

private:
	QString __mediaPath__;
	QString __workspace__;
	QString __exePath__;
	QStringList __env__;
	QStringList __args__;
	int base;
};

#endif
