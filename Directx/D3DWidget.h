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

	bool initialize();
	void d3dRender();
	void d3dResize();

private:
	GraphicsClass* m_Graphics;
};


