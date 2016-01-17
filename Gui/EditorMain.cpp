#include "EditorMain.h"
#include <QApplication>
#include <QCoreApplication> 
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "MainWindow.h"
#include "Settings.h"
#include <iostream>
#include <windows.h>  //需放在Qt库的后面
using namespace std;



int RunEditor(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWin(Q_NULLPTR, 0);
	mainWin.resize(1000, 600);
	mainWin.show();

	return app.exec();
}


//1 确保moc_.xx.cpp被包含(Generated Files中), 可移除再添加
//手动生成moc_.xx.cpp
//set PATH = E:\CODE\qt5_github\qt5_build\qtbase\bin
//moc dialog.h - o moc_dialog.cpp
//frame->setObjectName("myframe");
//frame->setStyleSheet("QFrame#myframe{border-image:url(images/frame.png)}");

