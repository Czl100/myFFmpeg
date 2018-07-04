#pragma once
#pragma execution_character_set("utf-8")

#ifndef _DECODER_CONFIG_H
#define _DECODER_CONFIG_H

#include "Config.h"
#include <QHash>
#include <QList>

class DecoderConfig : public Config{
public:
	DecoderConfig(QString &_fileName) : file(new QFile(_fileName)){
		if (file->exists()){	// 文件存在，则只读打开
			file->open(QIODevice::ReadOnly);
			// 读取一行，并认为文本和本地编码模式相同，并将其解码为QString。
			for (QString line(file->readLine()); line.size() != 0; line = file->readLine()){
				if (line.right(2) == "\r\n"){ line = line.left(line.size() - 2); }
				if (line.right(1) == "\n"){ line = line.left(line.size() - 1); }
				QStringList sharpParts = line.split("#");
				QStringList pointParts = sharpParts[0].split("........");
				QString realLine = pointParts[0];
				content.append(realLine.simplified());
			}
			file->close();
		}
	}
	~DecoderConfig(){
		if (file->isOpen()){
			file->close();
		}
		delete file;
	}

public:
	DecoderConfig *map(QString key, int idx){
		key2idx[key] = idx;
		return this;
	}
	void set(QString key, QString value) override{
		if (key2idx.contains(key)){		// 存在该key则可以更改数据
			int idx = key2idx[key];
			content[idx] = value;
		}
	}
	const QString get(QString key) const override {
		static QString empty = "";
		if (key2idx.contains(key)){		// 存在该key则可以更改数据
			int idx = key2idx[key];
			return content[idx];
		}
		return empty;
	}
	const QStringList keys() const override {
		return key2idx.keys();
	}
	void sync() override{
		file->open(QIODevice::WriteOnly);
		for (int i = 0; i < content.size(); i++){
			file->write((content[i]+"\n").toLocal8Bit());			// 编码成本地编码模式所指定的格式
		}
		file->flush();
		file->close();
	}

private:
	QFile *file;
	QHash<QString, int> key2idx;
	QList<QString> content;
};

#endif