#pragma once
#pragma execution_character_set("utf-8")

#ifndef _ENCODER_CONFIG_H
#define _ENCODER_CONFIG_H

#include "Config.h"
#include <QHash>
#include <QList>

class EncoderConfig : public Config{
public:
	EncoderConfig(const QString &_fileName) : file(new QFile(_fileName)){
		if (file->exists()){	// 文件存在，则只读打开
			file->open(QIODevice::ReadOnly);
			// 读取一行，并认为文本和本地编码模式相同，并将其解码为QString。
			for (QString line(QString::fromLocal8Bit(file->readLine())); line.size() != 0; line = file->readLine()){
				if (line.right(2) == "\r\n"){ line = line.left(line.size() - 2); }
				if (line.right(1) == "\n"){ line = line.left(line.size() - 1); }
				QStringList sharpParts = line.split("#");
				QString realLine = sharpParts[0];
				QStringList lineParts = realLine.split("=");
				if (lineParts.size() != 2 || lineParts[0].simplified().size() == 0 || lineParts[1].simplified().size() == 0){
					continue;
				}else{
					QString key = lineParts[0].simplified();
					QString value = lineParts[1].simplified();
					content[key] = value;
					linked.append(key);
				}
			}
			file->close();
		}
	}
	~EncoderConfig(){
		if (file->isOpen()){
			file->close();
		}
		delete file;
	}
public:
	void set(QString key, QString value) override{
		if (content.contains(key)){
			content[key] = value;
		}
	}
	const QString get(QString key) const override{
		static QString empty = "";
		if (content.contains(key)){		// 存在该key则可以更改数据
			return content[key];
		}
		return empty;
	}
	const QStringList keys() const override {
		return linked;
	}
	void sync() override{
		if (!file->exists()){ return; }
		file->open(QIODevice::WriteOnly);
		for (int i = 0; i < linked.size(); i++){
			QString key = linked[i];
			QString val = content[key];
			file->write((key+" = "+val+"\n").toLocal8Bit());		// 根据本地编码模式，将字符串编码为QByteArray.
		}
		file->flush();
		file->close();
	}

private:
	QHash<QString, QString> content;
	QList<QString> linked;
	QFile *file;
};

#endif