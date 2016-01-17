//定义该宏能够减少windows头文件的大小，使编译器不编译一些不必要的文件，加快编译时间
#define WIN32_LEAN_AND_MEAN

#include "mainwindow.h"
#include "toolbar.h"
#include <QStatusBar>
#include <QTextEdit>
#include <QMenu>
#include <QMap>
#include <QMenuBar>
#include <QIcon>
#include <QSize>
#include <QDockWidget>
#include "qtcommon.h"
#include "settings.h"
//#include "qt_win/win_knowledge.h"
//#include "D3DWin.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	QString sIconPath = CEditConfig::getInstance()->iconPath().c_str();
	sIconPath += "\\";
	setObjectName("MainWindow");
	setWindowTitle(CH("综合工具箱"));
	setWindowIcon(QIcon(sIconPath + "feng1.png"));

	//QTextEdit *center = new QTextEdit(this);
	//center->setReadOnly(true);
	//center->setMinimumSize(400, 205);
	//setCentralWidget(center);

	//D3DRenderWidget* widget = new D3DRenderWidget(this);
	//setCentralWidget(widget);

	setupMenuBar();
	setupToolBar();
	setupDockWidgets();
	
	statusBar()->showMessage(CH("状态栏"));
}

void MainWindow::setupMenuBar()
{
	QMenu *menu = menuBar()->addMenu(CH("&文件"));
	menu->addAction(CH("打开文件"));
	menu->addAction(CH("保存文件"));
	menu->addSeparator();
	menu->addAction(tr("&Quit"));

}

void MainWindow::setupToolBar()
{
	ToolBar *tb1 = new ToolBar(CH("Tool Bar 1"), this);
	m_ToolBar["toorbar1"] = tb1;
	addToolBar(tb1);  // 会自己释放吗？
	return;
	ToolBar *tb2 = new ToolBar(CH("Tool Bar 1"), this);
	m_ToolBar["toorbar2"] = tb2;
	addToolBar(tb2);
}

void MainWindow::setupDockWidgets()
{
	QDockWidget *dock1 = new QDockWidget(this, Qt::WindowFlags(0));
	dock1->setObjectName("dock1");
	dock1->setWindowTitle(CH("资料"));
	addDockWidget(Qt::LeftDockWidgetArea, dock1);
	//CKnowledgeWin *win1 = new CKnowledgeWin(this);
	//dock1->setWidget(win1);
	QSize size = dock1->size();
	size.setWidth(300);
	dock1->resize(size);
	dock1->setMinimumWidth(200);
}

void MainWindow::openFile()
{

}

void MainWindow::saveFile()
{

}

