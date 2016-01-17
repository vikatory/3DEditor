#include "EditorMain.h"
#include <QApplication>
#include <QCoreApplication> 
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "MainWindow.h"
#include "Settings.h"
#include <iostream>
#include <windows.h>  //�����Qt��ĺ���
using namespace std;



int RunEditor(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWin(Q_NULLPTR, 0);
	mainWin.resize(800, 600);
	mainWin.show();

	cout << CEditConfig::getInstance()->iconPath() << endl;
	return app.exec();
}


//1 ȷ��moc_.xx.cpp������(Generated Files��), ���Ƴ������
//�ֶ�����moc_.xx.cpp
//set PATH = E:\CODE\qt5_github\qt5_build\qtbase\bin
//moc dialog.h - o moc_dialog.cpp
//frame->setObjectName("myframe");
//frame->setStyleSheet("QFrame#myframe{border-image:url(images/frame.png)}");

