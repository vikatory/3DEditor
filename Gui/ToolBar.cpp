
#include "toolbar.h"
#include "settings.h"
#include "qtcommon.h"

#include <QMenu>
#include <QIcon>

ToolBar::ToolBar(const QString &title, QWidget *parent)
	: QToolBar(parent)
{
	setWindowTitle(title);
	setObjectName(title);

	setIconSize(QSize(32, 32));
	setIconSize(QSize(24, 24));
	QString sIconPath = CEditConfig::getInstance()->iconPath().c_str();
	sIconPath += "\\";

	QAction *openAct = addAction(QIcon(sIconPath + "open.png"), CH("打开"));
	QAction *saveAct = addAction(QIcon(sIconPath + "save.png"), CH("保存"));
	QAction *saveasAct = addAction(QIcon(sIconPath + "saveas.png"), CH("另存为"));
	QAction *closeAct = addAction(QIcon(sIconPath + "close.png"), CH("关闭"));

	QMenu *menu = new QMenu(CH("自定义1"), this);
	menu->setIcon(QIcon(sIconPath+"other1.png"));
	menu->addAction(QIcon(sIconPath + "other1.png"), "A");
	menu->addAction(QIcon(sIconPath + "other1.png"), "B");
	menu->addAction(QIcon(sIconPath + "other1.png"), "C");
	addAction(menu->menuAction());
	
}



