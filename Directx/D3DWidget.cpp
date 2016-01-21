#include "D3DWidget.h"

#include <QTimer>

D3DWidget::D3DWidget(QWidget *parent): QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));

	initialize();
}

D3DWidget::~D3DWidget()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}
}

void D3DWidget::resizeEvent(QResizeEvent *e)
{
	d3dResize();
}

void D3DWidget::paintEvent(QPaintEvent *e)
{
	d3dRender();
}

bool D3DWidget::initialize()
{
	bool result;
	int screenWidth = width(), screenHeight = height();

	// 创建图形对象，这个对象将渲染应用程序中的所有物体
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}
	// 初始化图形对象
	result = m_Graphics->Initialize(screenWidth, screenHeight, (HWND)winId());
	if (!result)
	{
		return false;
	}
}

void D3DWidget::d3dRender()
{
	bool result;

	// 执行帧渲染函数.
	result = m_Graphics->Frame();
	if (!result)
	{
		return;
	}
}

void D3DWidget::d3dResize()
{
	int screenWidth = width(), screenHeight = height();
	// 窗口大小改变时，重新初始化图形对象
	if (m_Graphics)
	{
		bool result = m_Graphics->Initialize(screenWidth, screenHeight, (HWND)winId());
		if (!result)
		{
			return;
		}
	}
}





