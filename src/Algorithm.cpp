#pragma once
#pragma execution_character_set("utf-8")

#include "Algorithm.h"

// ================================ 读出 ================================
const QString Algorithm::algo_name() {
	return __algoName__;
}
const QString Algorithm::workspace() {
	return __workspace__;
}
const QString Algorithm::encoder_path(){
	return __encoderPath__;
}
const QString Algorithm::decoder_path() {
	return __decoderPath__;
}

const QString Algorithm::exe_path(OperaType type) {
	return type == ENCODE ? __encoderPath__ : __decoderPath__;
}
const QHash<QString, QString> &Algorithm::param_map(OperaType type) {
	return __algoParams__[type];
}

// ================================ 写入 ================================
void Algorithm::add_param(OperaType type, const QString &key, const QString& val){
	__algoParams__[type][key] = val;
}
void Algorithm::del_param(OperaType type, const QString &key){
	__algoParams__[type].remove(key);
}
void Algorithm::clear_param(OperaType type){
	__algoParams__[type].clear();
}