#pragma once
#pragma execution_character_set("utf-8")

#ifndef _CONSOLE_WINDOW_H
#define _CONSOLE_WINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class ConsoleWindow : public QMainWindow{
	Q_OBJECT
public:
	ConsoleWindow(QWidget *parent = 0) : QMainWindow(parent){
		setWindowTitle("Console");
		setCentralWidget(new QTextEdit);
		setFixedSize(500, 600);
		QTextEdit * text = qobject_cast<QTextEdit *>(centralWidget());
		text->setReadOnly(true);
	}

public:
	void showEvent(QShowEvent *event) override{
		QTextEdit * text = qobject_cast<QTextEdit *>(centralWidget());
		text->clear();
		QMainWindow::showEvent(event);
	}

	void append(const QString &str){
		QTextEdit * text = qobject_cast<QTextEdit *>(centralWidget());
		text->append(str);
	}
};

#endif