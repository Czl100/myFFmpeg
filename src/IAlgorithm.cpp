#pragma once
#pragma execution_character_set("utf-8")

#include "IAlgorithm.h"
#include <QDir>

void IAlgorithm::load_env_args(OperaType type, QStringList &env, QStringList &args){
	QHash<QString, QString> &params = __algoParams__[type];
	QList<QString> &keys = params.keys();
	if (type == ENCODE){
		args.append("-d");
		args.append("../../encoder.cfg");
	}
	else{
		args.append("../../decoder.cfg");
	}
	for (int i = 0; i < keys.size(); i++){
		if (keys[i] != "args"){
			env.append(keys[i] + "=" + params[keys[i]]);
		}
		else{
			QStringList parts = params[keys[i]].split(" ");
			for (int i = 0; i < parts.size(); i++){
				args.append(parts[i]);
			}
		}
	}
}