#pragma once
#pragma execution_character_set("utf-8")

#include "VihThreadRunner.h"

OperaStatus VihThreadRunner::status(){
	return __status__;
}

bool VihThreadRunner::start(std::shared_ptr<VihThread> t){
	// 若还有线程在运行，则放弃运行新线程。
	if (__status__ == RUNNING){
		return false;
	}
	__t__ = t;
	connect(__t__.get(), &VihThread::algoMessageSignal, this, [&](int type, const QString &line, int val){
		// 停止
		if (val == 100){
			__status__ = STOP;
		}
		emit runnerSignal(type, line, val);
	});


	__t__->start();
	__status__ = RUNNING;
	return true;
}

void VihThreadRunner::stop(){
	if (__status__ != STOP){
		__t__->stop();
		// Runner认为线程已经结束了，线程自己会等处理完毕以后再结束。
		__status__ = STOP;
		emit runnerSignal(-1, "操作已经停止", 100);
	}
}
