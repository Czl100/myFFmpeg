#pragma once
#pragma execution_character_set("utf-8")

#ifndef __VIH_THREAD_RUNNER_H
#define __VIH_THREAD_RUNNER_H

#include "VihThread.h"
#include "defines.h"
#include <memory>
#include <QObject>

// 线程运行器。提交任务，运行任务。
class VihThreadRunner : public QObject{

	Q_OBJECT

public:
	VihThreadRunner() :__status__(STOP){}

signals:
	void runnerSignal(int type, const QString &line, int val);

public:
	bool start(std::shared_ptr<VihThread> t);
	OperaStatus status();
	void stop();

private:
	std::shared_ptr<VihThread> __t__;
	OperaStatus __status__;
};

#endif