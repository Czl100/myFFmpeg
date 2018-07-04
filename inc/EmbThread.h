#pragma once
#pragma execution_character_set("utf-8")

#ifndef __HIDE_THREAD_H
#define __HIDE_THREAD_H

#include "VihThread.h"
#include <memory>

class EmbThread : public VihThread{
	Q_OBJECT
public:
	EmbThread(std::shared_ptr<PanelStatusModel> model);
	~EmbThread(){}

protected:
	void run() override;

private:
	QString __mediaPath__;				// 原始多媒体文件路径
	QString __embMediaPath__;			// 输出的载密多媒体文件路径
	QString __workspace__;				// 嵌入算法进程的工作空间
	QString __exePath__;				// 嵌入算法进程的入口路径(可执行程序路径)
	QStringList __env__;				// 嵌入算法进程所需要的环境变量
	QStringList __args__;				// 嵌入算法进程所需要的输入参数
	int base;
	
};

#endif
