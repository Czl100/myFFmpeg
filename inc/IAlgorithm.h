#pragma once
#pragma execution_character_set("utf-8")

#ifndef __INTERFACE_ALGORITHM_H
#define __INTERFACE_ALGORITHM_H

#include <QString>
#include <memory>
#include "DecoderConfig.h"
#include "EncoderConfig.h"
#include "defines.h"

class IAlgorithm {

public:
	IAlgorithm(const QString &algorithmsDir, const QString &_algoName) :
		__algoName__(_algoName)
		{
			__exespace__ = algorithmsDir + "/" + __algoName__ + "/";
			__encoderPath__ = __exespace__ + "lencod.exe";
			__decoderPath__ = __exespace__ + "ldecod.exe";
			__workspace__ = __exespace__ + "/workspace";

	}

	virtual ~IAlgorithm(){}

public:
	virtual const QString algo_name() = 0;								// 获得算法的名字
	virtual const QString workspace() = 0;								// 获得算法工作路径
	virtual const QString encoder_path() = 0;							// 获得算法的编码器路径
	virtual const QString decoder_path() = 0;							// 获得算法解码器路径
	virtual const QString exe_path(OperaType type) = 0;					// 获得可执行文件路径
	virtual const QHash<QString, QString> &param_map(OperaType type) = 0;		// 获得输入参数的mapper

	virtual void add_param(OperaType type, const QString &key, const QString& val) = 0;		// 添加参数对
	virtual void del_param(OperaType type, const QString &key) = 0;							// 删除参数对
	virtual void clear_param(OperaType type) = 0;											// 清空参数

	// 默认参数加载方案，配置命令所需要的args和环境变量env
	virtual void load_env_args(OperaType type, QStringList &env, QStringList &args);

protected:
	QString __workspace__;
	QString __exespace__;
	const QString __algoName__;
	QString __encoderPath__;
	QString __decoderPath__;

	QHash<QString, QString> __algoParams__[2];	// 0-编码的参数模型， 1-解码的参数模型
};

#endif