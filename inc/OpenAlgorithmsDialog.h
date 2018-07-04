#pragma once
#pragma execution_character_set("utf-8")

#ifndef __OPEN_ALGORITHMS_DIALOG_H
#define __OPEN_ALGORITHMS_DIALOG_H

#include <QDialog>

class QGroupBox;
class QButtonGroup;
class QPushButton;

class OpenAlgorithmsDialog : public QDialog{
	Q_OBJECT

public:
	OpenAlgorithmsDialog(int idx, const QStringList& algoNameList, QWidget *parent = 0);
	~OpenAlgorithmsDialog(){}

public:
	int retval(){return __retval__;}

private:
	void init_layout();

private slots:
	void radios_slot(int idx);

private:
	QGroupBox* __algoBox__;
	QButtonGroup *__radioGroup__;
	QPushButton *__sureButton__;
	int __val__;
	int __old_val__;
	int __retval__;
};


#endif
