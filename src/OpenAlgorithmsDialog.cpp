#pragma once
#pragma execution_character_set("utf-8")

#include "OpenAlgorithmsDialog.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>

OpenAlgorithmsDialog::OpenAlgorithmsDialog(int idx, const QStringList& algoNameList, QWidget *parent) : QDialog(parent),
__algoBox__(new QGroupBox("算法")), __radioGroup__(new QButtonGroup(__algoBox__)), __sureButton__(new QPushButton("确定")){

	setWindowTitle("选择算法");
	init_layout();
	
	// 加入按钮
	for (int i = 0; i < algoNameList.size(); i++){
		QRadioButton *r = new QRadioButton(algoNameList[i]);
		if (i == idx){r->setChecked(true);}
		__radioGroup__->addButton(r);
		__algoBox__->layout()->addWidget(r);
	}

	connect(__radioGroup__, SIGNAL(buttonClicked(int)), this, SLOT(radios_slot(int)));
	connect(__sureButton__, &QPushButton::clicked, this, [&](){
		__retval__ = __val__;
		this->close();
	});

	__val__ = idx;
	__retval__ = idx;
}

void OpenAlgorithmsDialog::init_layout(){
	QBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);	

	__algoBox__->setLayout(new QVBoxLayout);

	layout->addWidget(__algoBox__);
	layout->addWidget(__sureButton__);
}

void OpenAlgorithmsDialog::radios_slot(int idx){
	__val__ = - 2 - idx;		// 我也不知道为什么有-2的偏移
}