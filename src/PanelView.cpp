#pragma once
#pragma execution_character_set("utf-8")

#include "PanelView.h"
#include "IPanelController.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QProgressBar>
#include <QLabel>
#include <QAction>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QGroupBox>
#include <QDebug>

PanelView::PanelView(QWidget *parent) : IPanelView(parent),
__player__(new QMediaPlayer()), 
__playButton__(new QPushButton("播放")), __openMediaButton__(new QPushButton("打开")), __embShowButton__(new QPushButton("信息嵌入")),
__extShowButton__(new QPushButton("信息提取")), __embWidget__(new QGroupBox("嵌入面板")), __embProgress__(new QProgressBar),
__embSecretEdit__(new QLineEdit), __embMediaEdit__(new QLineEdit), __openEmbSecretButton__(new QPushButton("..")),
__openEmbMediaButton__(new QPushButton("..")), __embButton__(new QPushButton("嵌入")),
__extWidget__(new QGroupBox("提取面板")), __openExtSecretButton__(new QPushButton("..")), __extSecretEdit__(new QLineEdit),
__extProgress__(new QProgressBar), __extButton__(new QPushButton("提取")){
	
	setWindowTitle("视频信息隐藏系统");
	__embProgress__->setRange(0, 100);
	__embProgress__->setValue(0);
	__extProgress__->setRange(0, 100);
	__extProgress__->setValue(0);
	__openEmbSecretButton__->setFixedSize(22, 22);
	__openEmbMediaButton__->setFixedSize(22, 22);
	__openExtSecretButton__->setFixedSize(22, 22);
	__embWidget__->setFixedHeight(110);
	__extWidget__->setFixedHeight(90);
	__init_layout__();
}

void PanelView::__init_layout__(){
	// 1).配置中心组件以及基础布局
	setCentralWidget(new QWidget);
	QVBoxLayout *panelLayout = new QVBoxLayout;
	centralWidget()->setLayout(panelLayout);

	// 2).添加视频播放相关组件布局
	QVBoxLayout * playerLayout = new QVBoxLayout;
	QHBoxLayout * playerButtonLayout = new QHBoxLayout;
	QVideoWidget* vw = new QVideoWidget();
		// 2.1).配置videoWidget的属性
		vw->setMinimumSize(500, 400);
		QPalette pal(vw->palette());
		pal.setColor(QPalette::Background, Qt::black);
		vw->setAutoFillBackground(true);
		vw->setPalette(pal);
	__player__->setVideoOutput(vw);
	playerButtonLayout->addWidget(__openMediaButton__);
	playerButtonLayout->addWidget(__playButton__);
	playerButtonLayout->addWidget(__embShowButton__);
	playerButtonLayout->addWidget(__extShowButton__);
	playerLayout->addWidget(vw);
	playerLayout->addLayout(playerButtonLayout);

	// 3).信息嵌入界面
	QVBoxLayout* embLayout = new QVBoxLayout;
	__embWidget__->setLayout(embLayout);
		// 3.1).
		QHBoxLayout* embSecLayout = new QHBoxLayout;
		embSecLayout->addWidget(new QLabel("秘密文件"));
		embSecLayout->addWidget(__embSecretEdit__);
		embSecLayout->addWidget(__openEmbSecretButton__);
		// 3.2).
		QHBoxLayout* embMediaLayout = new QHBoxLayout;
		embMediaLayout->addWidget(new QLabel("载密视频"));
		embMediaLayout->addWidget(__embMediaEdit__);
		embMediaLayout->addWidget(__openEmbMediaButton__);
		// 3.3).
		QHBoxLayout* embStartLayout = new QHBoxLayout;
		__embWidget__->setLayout(embStartLayout);
		embStartLayout->addWidget(new QLabel("工作进度"));
		embStartLayout->addWidget(__embProgress__);			// 进度条
		embStartLayout->addWidget(__embButton__);			// 按钮
	embLayout->addLayout(embSecLayout);
	embLayout->addLayout(embMediaLayout);
	embLayout->addLayout(embStartLayout);
	__embWidget__->hide();

	// 4).信息提取解码
	QVBoxLayout* extLayout = new QVBoxLayout;
	__extWidget__->setLayout(extLayout);
		// 4.1).
		QHBoxLayout* extSecLayout = new QHBoxLayout;
		extSecLayout->addWidget(new QLabel("秘密文件"));
		extSecLayout->addWidget(__extSecretEdit__);
		extSecLayout->addWidget(__openExtSecretButton__);
		// 4.2).
		QHBoxLayout* extStartLayout = new QHBoxLayout;
		__extWidget__->setLayout(extStartLayout);
		extStartLayout->addWidget(new QLabel("工作进度"));
		extStartLayout->addWidget(__extProgress__);			// 进度条
		extStartLayout->addWidget(__extButton__);			// 按钮
	extLayout->addLayout(extSecLayout);
	extLayout->addLayout(extStartLayout);
	__extWidget__->hide();

	// 5).
	panelLayout->addLayout(playerLayout);
	panelLayout->addWidget(__embWidget__);
	panelLayout->addWidget(__extWidget__);

	// 6).菜单栏
	__openAlgorithmAction__ = new QAction("算法选择", this);
	__openConsoleAction__ = new QAction("调试台", this);
	QMenu *toolMenu = menuBar()->addMenu("工具箱");
	toolMenu->addAction(__openAlgorithmAction__);
	toolMenu->addAction(__openConsoleAction__);
}

void PanelView::link_controller(const IPanelController &controller){
	// 打开多媒体选择目录的按钮事件注册
	connect(__openMediaButton__, SIGNAL(clicked()), &controller, SLOT(open_video_slot()));

	// 播放按钮事件注册
	connect(__playButton__, SIGNAL(clicked()), &controller, SLOT(play_video_slot()));

	// 显示和隐藏 信息隐藏相关的操作。
	connect(__embShowButton__, &QPushButton::clicked, this, [=](){
		if (__embWidget__->isHidden()){
			__extWidget__->hide();
			__embWidget__->show();
		}
		else{
			__embWidget__->hide();
		}
	});

	connect(__extShowButton__, &QPushButton::clicked, this, [=](){
		if (__extWidget__->isHidden()){
			__embWidget__->hide();
			__extWidget__->show();
		}
		else{
			__extWidget__->hide();
		}
	});

	// 
	connect(__openAlgorithmAction__, SIGNAL(triggered()), &controller, SLOT(open_algorithm_slot()));
	connect(__openConsoleAction__, SIGNAL(triggered()), &controller, SLOT(open_console_slot()));

	connect(__openEmbSecretButton__, SIGNAL(clicked()), &controller, SLOT(open_emb_secert_slot()));
	connect(__openEmbMediaButton__, SIGNAL(clicked()), &controller, SLOT(save_emb_media_slot()));
	connect(__embButton__, SIGNAL(clicked()), &controller, SLOT(start_emb_slot()));


	connect(__openExtSecretButton__, SIGNAL(clicked()), &controller, SLOT(save_ext_secert_slot()));


	connect(__extButton__, SIGNAL(clicked()), &controller, SLOT(start_ext_slot()));

	connect(__embSecretEdit__, SIGNAL(textChanged(const QString&)), &controller, SLOT(emb_secret_change_slot(const QString&)));
	connect(__embMediaEdit__, SIGNAL(textChanged(const QString&)), &controller, SLOT(emb_media_change_slot(const QString&)));
	connect(__extSecretEdit__, SIGNAL(textChanged(const QString&)), &controller, SLOT(ext_secret_change_slot(const QString&)));
}