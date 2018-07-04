#pragma once
#pragma execution_character_set("utf-8")

#ifndef __ALGORITHM_BUILDER_H
#define __ALGORITHM_BUILDER_H

#include <QString>
#include "IAlgorithm.h"

class AlgorithmBuilder{
public:
	IAlgorithm *build(const QString& algorithmsDir, const QString &_algoName){
		// 校验
		QString lencodPath = algorithmsDir + "/" + _algoName + "/lencod.exe";
		QString ldecodPath = algorithmsDir + "/" + _algoName + "/ldecod.exe";
		QString workspacePath = algorithmsDir + "/" + _algoName + "/workspace/";

		QFileInfo lencodFileInfo(lencodPath);
		QFileInfo ldecodFileInfo(lencodPath);
		QFileInfo workspaceFileInfo(lencodPath);


		if (
		(!lencodFileInfo.exists()) ||
		(!ldecodFileInfo.exists()) ||
		(!workspaceFileInfo.exists())
		){
			return nullptr;
		}

		// 创建
		return ctor(algorithmsDir, _algoName);
	}
private:
	// 该函数的职责是 调用算法的构造函数并返回
	virtual IAlgorithm *ctor(const QString& algorithmsDir, const QString &_algoName) = 0;
};

#endif
