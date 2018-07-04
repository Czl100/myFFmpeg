#pragma once
#pragma execution_character_set("utf-8")

#include "utils.h"
#include "defines.h"
#include <QDateTime>
#include <QTextStream>
#include "EncoderConfig.h"

using namespace std;

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
	static QMutex mutex;
	mutex.lock();

	QByteArray localMsg = msg.toLocal8Bit();
	QString strMsg("");

	switch (type){
	case QtDebugMsg: strMsg = QString("Debug:"); break;
	case QtWarningMsg: strMsg = QString("Warning:"); break;
	case QtCriticalMsg: strMsg = QString("Critical:"); break;
	case QtFatalMsg: strMsg = QString("Fatal:"); break;
	}

	QString strDateTime = QDateTime::currentDateTime().toString();
	QString strMessage = QString("Message:%1 File:%2 Line:%3 Function:%4 DateTime%5")
		.arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);

	QFile output("log");
	output.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream os(&output);
	os << strMessage.toLocal8Bit() << endl;
	output.flush();
	output.close();

	mutex.unlock();
}