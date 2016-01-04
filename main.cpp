


#include <QApplication>
#include <QCoreApplication> 
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <windows.h>  //需放在Qt库的后面
using namespace std;

#define DEBUG   1
#define EDITOR  0

//
//int RunEditor(int argc, char *argv[])
//{
//	QApplication app(argc, argv);
//
//	Dialog dialog;
//	dialog.show();
//
//	MainWindow mainWin(Q_NULLPTR, 0);
//	mainWin.resize(800, 600);
//	mainWin.show();
//
//	cout << GetCurrentPath() << endl;
//	cout << CEditConfig::getInstance()->iconPath() << endl;
//	cout << 888888888 << endl;
//	return app.exec();
//}



int main(int argc, char *argv[])
{
#ifdef DEBUG
	AllocConsole();    //为进程创造一个新的控制台
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

#if(EDITOR == 1)
	RunEditor(argc, argv);
#else
	//PyEngine *pPyEngine = new PyEngine();
	//pPyEngine->test();

	system("pause");

	//delete pPyEngine;
#endif

#ifdef DEBUG
	FreeConsole();
#endif
	return 0;
}

//1 确保moc_.xx.cpp被包含(Generated Files中), 可移除再添加
//手动生成moc_.xx.cpp
//set PATH = E:\CODE\qt5_github\qt5_build\qtbase\bin
//moc dialog.h - o moc_dialog.cpp
//frame->setObjectName("myframe");
//frame->setStyleSheet("QFrame#myframe{border-image:url(images/frame.png)}");

