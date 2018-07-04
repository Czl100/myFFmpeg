#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QApplication>
#include <QtCore/QDir>
#include <PanelController.h>
#include <PanelView.h>
#include <PanelStatusModel.h>
#include <memory>
#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>
#include <QProcessEnvironment>
#include "AlgoConf.h"
#include "LHHAlgorithm.h"
#include "WTQAlgorithm.h"
#include "LSJAlgorithm.h"
#include "defines.h"
#include "utils.h"

using namespace std;

bool check_load_model(shared_ptr<PanelStatusModel> m){
	QString algorithmsRootDir = "algorithms/";
	// 建立builder映射
	QHash<QString, AlgorithmBuilder*> builderMap;
	builderMap.insert("LHH", new LHHBuilder());
	builderMap.insert("WTQ", new WTQBuilder());
	builderMap.insert("LSJ", new LSJBuilder());

	// 临时文件夹
	QFileInfo tmpinfo("tmp");
	if (!tmpinfo.exists()){
		qDebug() << "[Exception] tmp dir not exists";
		return false;
	}

	// 算法配置文件
	if (! AlgoConf::open_algorithm_config(algorithmsRootDir)){
		qDebug() << "[Exception] algoritum dir open error";
		return false;
	}

	// 算法运行环境初始化
	QFileInfo cfginfo(app_config_path());
	if (!cfginfo.exists()){
		qDebug() << "[Exception] app.cfg not exists";
		return false;
	}
	EncoderConfig cfg(app_config_path());
	QString algorithms = cfg.get("algorithms");
	QStringList algorithmList = algorithms.split(";");
	for (int i = 0; i < algorithmList.size(); i++){
		QString &algorithm = algorithmList[i].simplified();
		if (!(algorithm.startsWith('[') && algorithm.endsWith(']'))){
			qDebug() << "[Exception] algorithm package need '[]'";
			return false;
		}
		QStringList parts = algorithm.mid(1, algorithm.size() - 2).split(",");
		if (parts.size() != 2){
			qDebug() << "[Exception] algorithm package need use ',' to split";
			return false;
		}
		QString &aname = parts[0].simplified();
		QString &builderName = parts[1].simplified();
		AlgorithmBuilder *builder = builderMap[builderName];
		if (!builder){
			qDebug() << "[Exception] '" + builderName + "'builder not exists";
			return false;
		}
		IAlgorithm *algo = builder->build(algorithmsRootDir, aname);
		if (!algo){
			qDebug() << "[Exception] '" + aname + "'algorithm construct wrong, please verify the file and dir is exist";
			return false;
		}
		m->add_algorithm(shared_ptr<IAlgorithm>(algo));
	}
	return true;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// 配置工作路径为exe文件所在路径
	QDir::setCurrent(QCoreApplication::applicationDirPath()+"/workspace/");

	// 配置日志系统(DEBUG模式下输出到控制台，RELEASE模式下输出到日志文件)
#ifndef _DEBUG
	qInstallMessageHandler(customMessageHandler);	// 自定义日志输出
#endif

	// 构建MVC
	qDebug() << "=========================================================================================";
	shared_ptr<PanelController> c = shared_ptr<PanelController>(new PanelController);
	shared_ptr<PanelView> v = shared_ptr<PanelView>(new PanelView);
	shared_ptr<PanelStatusModel> m = shared_ptr<PanelStatusModel>(new PanelStatusModel);
	// 链接MVC
	if (check_load_model(m)){
		c->set_view(v);
		c->set_status_model(m);

		v->show();
		qDebug() << "Video Information Hide System is running...";
		return a.exec();
	}
	else{
		QMessageBox::critical(nullptr, "视频信息隐藏系统", "系统构建失败，请查看日志查询错误信息", QMessageBox::Yes);
	}
	
}


