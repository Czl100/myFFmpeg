#pragma once
#pragma execution_character_set("utf-8")

#ifndef __ALGO_CONF_H
#define __ALGO_CONF_H

#include <QString>
#include <memory>
#include "Config.h"
#include "EncoderConfig.h"
#include "DecoderConfig.h"
#include "defines.h"

class AlgoConf{
public:
	// 打开算法配置文件
	static bool open_algorithm_config(const QString &algorithmsDir);
	// 同步
	static void sync(OperaType type);
	

	// 读出
	static const QString encoder_cfg_path();						// 获得编码器配置文件路径
	static const QString decoder_cfg_path();						// 获得解码器配置文件路径
	static const Config &config(OperaType type);					// 直接返回配置文件
	static const QString get(OperaType type, const QString& key);	// 获取配置文件的值
	static int encode_width();										// 编码的宽度
	static int encode_height();										// 编码的高度
	static int encode_frames();										// 编码的帧数
	static int encode_fps();										// 编码的码率
	static const QString input_file_path(OperaType type);			// 读出输入的文件路径
	static const QString output_file_path(OperaType type);			// 读出输出的文件路径
	static const QString emb_secret_path();
	static const QString ext_secret_path();

	// 写入
	static void set(const QString &key, const QString& val, OperaType type);
	static void encode_width_height(int w, int h);
	static void encode_width(int w);										// 编码的宽度
	static void encode_height(int h);										// 编码的高度
	static void encode_frames(const int frames);							// 设置编码帧数
	static void encode_fps(const int fps);									// 设置码率
	static void output_file_path(OperaType type, const QString &path);		// 设置输出的文件路径
	static void input_file_path(OperaType type, const QString &path);		// 设置输入的文件路径
	static void emb_secret_path(const QString& path);
	static void ext_secret_path(const QString& path);

protected:
	static std::shared_ptr<Config> s_cfg[2];			// 0-编码的配置文件， 1-解码得配置文件
	static QString s_encoderCfgPath;
	static QString s_decoderCfgPath;
	static bool s_isopenAlgoConfig;
	static QString s_embSecretPath;
	static QString s_extSecretPath;
};

#endif