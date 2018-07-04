#pragma once
#pragma execution_character_set("utf-8")

#ifndef __VIH_THREAD_H
#define __VIH_THREAD_H

#include <QThread>
#include <QString>
#include <QStringList>
#include <memory>
#include <QProcess>
#include "PanelStatusModel.h"
#include "defines.h"

class AlgosModel;

class VihThread : public QThread{
	Q_OBJECT
public:
	VihThread() : stopped(true){}
	virtual ~VihThread(){}

signals:
	void algoMessageSignal(int type, const QString &line, int val);

public slots:
	void processErrorSlot(QProcess::ProcessError error);

public:
	void stop();

protected:
	volatile bool stopped;
	OperaType __type__;
};

#endif
