//����ú��ܹ�����windowsͷ�ļ��Ĵ�С��ʹ������������һЩ����Ҫ���ļ����ӿ����ʱ��
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
#include "Directx\D3DWin.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	QString sIconPath = CEditConfig::getInstance()->iconPath().c_str();
	sIconPath += "\\";
	setObjectName("MainWindow");
	setWindowTitle(CH("�ۺϹ�����"));
	setWindowIcon(QIcon(sIconPath + "feng1.png"));

	//QTextEdit *center = new QTextEdit(this);
	//center->setReadOnly(true);
	//center->setMinimumSize(400, 205);
	//setCentralWidget(center);

	D3DRenderWidget* widget = new D3DRenderWidget(this);
	setCentralWidget(widget);

	setupMenuBar();
	setupToolBar();
	setupDockWidgets();
	
	statusBar()->showMessage(CH("״̬��"));
}

void MainWindow::setupMenuBar()
{
	QMenu *menu = menuBar()->addMenu(CH("&�ļ�"));
	menu->addAction(CH("���ļ�"));
	menu->addAction(CH("�����ļ�"));
	menu->addSeparator();
	menu->addAction(tr("&Quit"));

}

void MainWindow::setupToolBar()
{
	ToolBar *tb1 = new ToolBar(CH("Tool Bar 1"), this);
	m_ToolBar["toorbar1"] = tb1;
	addToolBar(tb1);  // ���Լ��ͷ���
	return;
	ToolBar *tb2 = new ToolBar(CH("Tool Bar 1"), this);
	m_ToolBar["toorbar2"] = tb2;
	addToolBar(tb2);
}

void MainWindow::setupDockWidgets()
{
	QDockWidget *dock1 = new QDockWidget(this, Qt::WindowFlags(0));
	dock1->setObjectName("dock1");
	dock1->setWindowTitle(CH("����"));
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

