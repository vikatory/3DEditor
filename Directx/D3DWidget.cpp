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

	// ����ͼ�ζ������������ȾӦ�ó����е���������
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}
	// ��ʼ��ͼ�ζ���
	result = m_Graphics->Initialize(screenWidth, screenHeight, (HWND)winId());
	if (!result)
	{
		return false;
	}
}

void D3DWidget::d3dRender()
{
	bool result;

	// ִ��֡��Ⱦ����.
	result = m_Graphics->Frame();
	if (!result)
	{
		return;
	}
}

void D3DWidget::d3dResize()
{
	int screenWidth = width(), screenHeight = height();
	// ���ڴ�С�ı�ʱ�����³�ʼ��ͼ�ζ���
	if (m_Graphics)
	{
		bool result = m_Graphics->Initialize(screenWidth, screenHeight, (HWND)winId());
		if (!result)
		{
			return;
		}
	}
}





