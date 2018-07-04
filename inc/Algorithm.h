#pragma once
#pragma execution_character_set("utf-8")

#ifndef _ALGORITHM_PROCESS_INFORMATION_H
#define _ALGORITHM_PROCESS_INFORMATION_H

#include "IAlgorithm.h"

class Algorithm : public IAlgorithm{

public:
	Algorithm(const QString &algorithmsDir, const QString &_algoName) :IAlgorithm(algorithmsDir, _algoName){}

public:
	const QString algo_name() override;
	const QString workspace() override;
	const QString encoder_path()override;
	const QString decoder_path() override;
	const QString exe_path(OperaType type) override;
	const QHash<QString, QString> &param_map(OperaType type) override;

	void add_param(OperaType type, const QString &key, const QString& val) override;
	void del_param(OperaType type, const QString &key) override;
	void clear_param(OperaType type) override;
};

#endif