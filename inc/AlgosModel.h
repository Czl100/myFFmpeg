#pragma once
#pragma execution_character_set("utf-8")

#ifndef __ALGOS_MODEL_H
#define __ALGOS_MODEL_H

#include <memory>
#include <QList>
#include "IAlgorithm.h"
#include "defines.h"

class AlgosModel{
	
public:
	AlgosModel();
	virtual ~AlgosModel(){}

// 读函数
public:
	QString workspace();
	QString exe_path();
	const QStringList algos_list();
	int algo_idx();
	OperaType opera_type();
	QString algo_name();
	void load_env_args(QStringList &env, QStringList &args);

// 写函数
public:
	void add_algorithm(std::shared_ptr<IAlgorithm> algorithm);
	void algo_idx(int idx);
	void opera_type(OperaType type);
	

protected:
	QList<std::shared_ptr<IAlgorithm>> __algos__;
	int __algoIdx__;
	OperaType __operaType__;
};

#endif