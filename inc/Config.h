#pragma once
#pragma execution_character_set("utf-8")

#ifndef _CONFIG_H
#define _CONFIG_H

#include <QFile>
#include <QString>

class Config {
public:
	virtual void set(QString key, QString value)=0;
	virtual const QString get(QString key) const =0;
	virtual void sync() = 0;
	virtual const QStringList keys() const = 0;
};

#endif