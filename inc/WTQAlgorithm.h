#pragma once
#pragma execution_character_set("utf-8")

#ifndef _WTQ_ALGORITHM_H
#define _WTQ_ALGORITHM_H

#include "AlgoConf.h"
#include "Algorithm.h"

class WTQAlgorithm : public Algorithm{
public:
	WTQAlgorithm(const QString& algorithmsDir, const QString &_algoName) : Algorithm(algorithmsDir, _algoName){}
public:
	void load_env_args(OperaType type, QStringList &env, QStringList &args) override {
		Algorithm::load_env_args(type, env, args);
		if (type == ENCODE){
			
			int idx1 = AlgoConf::emb_secret_path().lastIndexOf("/");
			int idx2 = AlgoConf::emb_secret_path().lastIndexOf("\\");
			int idx = idx1 > idx2 ? idx1 : idx2;
			QString fileName = AlgoConf::emb_secret_path().right(AlgoConf::emb_secret_path().size() - idx - 1);
			args.append(fileName);
			args.append(AlgoConf::emb_secret_path());
			args.append("4");
		}
		else{
			args.append("4");
			args.append(AlgoConf::ext_secret_path());
		}
	}

};

class WTQBuilder : public AlgorithmBuilder{
	IAlgorithm *ctor(const QString& algorithmsDir, const QString &_algoName) override{
		return new WTQAlgorithm(algorithmsDir, _algoName);
	}
};

#endif