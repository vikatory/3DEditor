#pragma once

#include <QToolBar>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QActionGroup)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSpinBox)

class ToolBar : public QToolBar
{
	Q_OBJECT

public:
	explicit ToolBar(const QString &title, QWidget *parent);

	//QMenu *toolbarMenu() const { return menu; }

	private slots:
	//void updateMenu();

private:
};


