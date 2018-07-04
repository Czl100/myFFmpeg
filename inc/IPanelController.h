#pragma once
#pragma execution_character_set("utf-8")

#ifndef __INTERFACE_PANEL_CONTROLLER_
#define __INTERFACE_PANEL_CONTROLLER_

#include <QtCore/QObject>
#include <memory>

class IPanelView;
class PanelStatusModel;

class IPanelController : public QObject{
	Q_OBJECT
public:
	IPanelController():__view__(nullptr){}
	~IPanelController(){ }	
	void set_view(std::shared_ptr<IPanelView> view);
	void set_status_model(std::shared_ptr<PanelStatusModel> model);

public slots :

	virtual void open_video_slot() = 0;			// 打开目录选择视频文件
	virtual void play_video_slot() = 0;			// 播放视频
	virtual void play_progress_slot() = 0;		// 调整进度条

	virtual void open_emb_secert_slot() = 0;	// 打开目录选择秘密文件
	virtual void save_emb_media_slot() = 0;		// 保存载密多媒体文件的目录
	virtual void start_emb_slot() = 0;			// 开始视频信息隐藏


	virtual void save_ext_secert_slot() = 0;	// 选择提取数据的保存路径
	virtual void start_ext_slot() = 0;			// 开始视频信息提取



	virtual void open_algorithm_slot() = 0;		// 选择算法
	virtual void open_console_slot() = 0;		// 打开调试台

	virtual void emb_media_change_slot(const QString& line) = 0;
	virtual void ext_secret_change_slot(const QString& line) = 0;
	virtual void emb_secret_change_slot(const QString& line) = 0;

protected:
	std::shared_ptr<IPanelView> __view__;
	std::shared_ptr<PanelStatusModel> __statusModel__;
};

#endif