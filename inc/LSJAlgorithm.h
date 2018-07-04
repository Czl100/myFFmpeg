#pragma once
#pragma execution_character_set("utf-8")

#ifndef _LSJ_ALGORITHM_H
#define _LSJ_ALGORITHM_H

#include "AlgoConf.h"
#include "Algorithm.h"
#include "AlgorithmBuilder.h"

class LSJAlgorithm : public Algorithm{
public:
	LSJAlgorithm(const QString& algorithmsDir, const QString &_algoName) : Algorithm(algorithmsDir, _algoName){}
public:
	void load_env_args(OperaType type, QStringList &env, QStringList &args) override {
		Algorithm::load_env_args(type, env, args);
		type == ENCODE ? args.append(AlgoConf::emb_secret_path()) : args.append(AlgoConf::ext_secret_path());
	}
};

class LSJBuilder : public AlgorithmBuilder{
	IAlgorithm *ctor(const QString& algorithmsDir, const QString &_algoName) override{
		return new LSJAlgorithm(algorithmsDir, _algoName);
	}
};


#endif