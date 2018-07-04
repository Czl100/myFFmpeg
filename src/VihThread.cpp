#pragma once
#pragma execution_character_set("utf-8")

#include "VihThread.h"

#include <QDebug>
#include <string>
#include <memory>

using namespace std;

void VihThread::processErrorSlot(QProcess::ProcessError error){
	// 进程的运行出现问题，将会导致异常结束。
	if (stopped){
		//emit algoMessageSignal(__type__, "Stop Process", 100);
		//stopped 由runner负责抛出
	}
	else{
		switch (error){
		case QProcess::FailedToStart: emit algoMessageSignal(__type__, "FailedToStart", 100);  break;
		case QProcess::Crashed: emit algoMessageSignal(__type__, "Crashed", 100);  break;
		case QProcess::Timedout: emit algoMessageSignal(__type__, "Timedout", 100);  break;
		case QProcess::ReadError: emit algoMessageSignal(__type__, "ReadError", 100);  break;
		case QProcess::WriteError: emit algoMessageSignal(__type__, "WriteError", 100);  break;
		case QProcess::UnknownError: emit algoMessageSignal(__type__, "UnknownError", 100); break;
		default:emit algoMessageSignal(__type__, "Error", 100); break;
		}
	}
}

void VihThread::stop(){
	stopped = true;
}