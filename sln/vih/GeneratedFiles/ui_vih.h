/********************************************************************************
** Form generated from reading UI file 'vih.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIH_H
#define UI_VIH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vihClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *vihClass)
    {
        if (vihClass->objectName().isEmpty())
            vihClass->setObjectName(QStringLiteral("vihClass"));
        vihClass->resize(600, 400);
        menuBar = new QMenuBar(vihClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        vihClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(vihClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        vihClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(vihClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        vihClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(vihClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        vihClass->setStatusBar(statusBar);

        retranslateUi(vihClass);

        QMetaObject::connectSlotsByName(vihClass);
    } // setupUi

    void retranslateUi(QMainWindow *vihClass)
    {
        vihClass->setWindowTitle(QApplication::translate("vihClass", "vih", 0));
    } // retranslateUi

};

namespace Ui {
    class vihClass: public Ui_vihClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIH_H
