#pragma once

#include <QWidget>

#include <dxgi.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <assert.h>
#include "GraphicsClass.h"

class QResizeEvent;
class QPaintEvent;

#define safe_release(x)		 { if(x) { (x)->Release(); (x) = 0;	} }

class D3DWidget : public QWidget
{
	Q_OBJECT

public:
	D3DWidget(QWidget *parent = NULL);
	~D3DWidget();

	virtual QPaintEngine* paintEngine() const { return NULL; }

protected:
	virtual void resizeEvent(QResizeEvent *e);
	virtual void paintEvent(QPaintEvent *e);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent * event);
	virtual void keyPressEvent(QKeyEvent *event);

	bool initialize();
	void d3dRender();
	void d3dResize();

private:
	GraphicsClass* m_Graphics;

	int m_StartMoveX;
	int m_StartMoveY;
	XMFLOAT3 m_CameraPos;
};


