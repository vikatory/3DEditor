#pragma once

#include "toolbar.h"
#include <QMap>
#include <QMainWindow>

class QMenu;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	typedef QMap<QString, QSize> CustomSizeHintMap;

	explicit MainWindow(QWidget *parent = Q_NULLPTR,
						Qt::WindowFlags flags = 0);

	public slots:
	//void actionTriggered(QAction *action);
	void openFile();
	void saveFile();
	//void switchLayoutDirection();
	//void setDockOptions();

	//void createDockWidget();
	//void destroyDockWidget(QAction *action);

private:
	void setupToolBar();
	void setupMenuBar();
	void setupDockWidgets();

	//QList<ToolBar*> toolBars;
	QMap<QString, ToolBar*> m_ToolBar;
	QMenu *dockWidgetMenu;
	QMenu *mainWindowMenu;
	QList<QDockWidget *> extraDockWidgets;
	QMenu *destroyDockWidgetMenu;
};




