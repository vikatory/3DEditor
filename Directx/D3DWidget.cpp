#include "D3DWidget.h"
#include <QKeyEvent>
#include <QTimer>
#include <iostream>
#include <DirectxMath.h>
using namespace DirectX;
using namespace std;

const float PI = 3.14159265358979323f;


D3DWidget::D3DWidget(QWidget *parent): QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	setFocusPolicy(Qt::StrongFocus);
	initialize();
	timer->start(1000 / 60);
}

D3DWidget::~D3DWidget()
{
	// �ͷż�ʱ������.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

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

void D3DWidget::mousePressEvent(QMouseEvent *event)
{
	m_StartMoveX = event->x();
	m_StartMoveY = event->y();
	m_Graphics->m_Camera->getPosition(&m_CameraPos);
	//cout << 11111111 << endl;
}

void D3DWidget::mouseMoveEvent(QMouseEvent *event)
{
	int nDeltaX = event->x() - m_StartMoveX;
	int nDeltaY = event->y() - m_StartMoveY;
	if (event->modifiers() & Qt::AltModifier)
	{
		switch (event->buttons())
		{
		case Qt::LeftButton:
			cout << "��ת�����" << endl;
			break;
		case Qt::MidButton:
			cout << "ƽ�������" << endl;
			cout << nDeltaX << "  " << nDeltaY << endl;
			m_Graphics->m_Camera->strafe(-nDeltaX);
			update();
			break;
		case Qt::RightButton:
			cout << "ҡ�������" << endl;
			break;
		default:
			break;
		}
	}
	//cout << 222222222222 << "  "<<event->buttons()<< endl;
}

void D3DWidget::mouseReleaseEvent(QMouseEvent *event)
{
	//cout << 3333333 << endl;
}

void D3DWidget::wheelEvent(QWheelEvent * event)
{
	cout << "ҡ�������" << endl;
}

void D3DWidget::keyPressEvent(QKeyEvent *event)
{
	
	switch (event->key())
	{

	case Qt::Key_W:	//ǰ��
		cout << "w" << endl;
		m_Graphics->m_Camera->walk(-0.1);
		break;
	case Qt::Key_S:
		m_Graphics->m_Camera->walk(0.1);
		cout << "s" << endl;
		break;
	case Qt::Key_A:	//����
		m_Graphics->m_Camera->strafe(-0.1);
		cout << "a" << endl;
		break;
	case Qt::Key_D:
		m_Graphics->m_Camera->strafe(0.1);
		cout << "d" << endl;
		break;
	case Qt::Key_Q:	//����
		m_Graphics->m_Camera->fly(-0.1);
		cout << "q" << endl;
		break;
	case Qt::Key_E:
		m_Graphics->m_Camera->fly(0.1);
		cout << "e" << endl;
		break;
	case Qt::Key_Z:
		m_Graphics->m_Camera->pitch(PI / 180);
		cout << "z" << endl;
		break;
	case Qt::Key_X:
		m_Graphics->m_Camera->yaw(PI / 180);
		cout << "x" << endl;
		break;
	case Qt::Key_C:
		m_Graphics->m_Camera->roll(PI / 180);
		cout << "c" << endl;
		break;
	case Qt::Key_R://�������λ	
	{
		// ���������λ��.
		m_Graphics->m_Camera->Reset();
		XMFLOAT3 campos = XMFLOAT3(0.0f, 0.0f, -10.0f);
		m_Graphics->m_Camera->setPosition(&campos);
		cout << "x" << endl;
		break;
	}
	default:
		break;
	}
	update();
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

	// ������ʱ������.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// ��ʼ����ʱ������
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox((HWND)winId(), L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}
}

void D3DWidget::d3dRender()
{
	bool result;

	m_Timer->Frame();

	// ִ��֡��Ⱦ����.
	result = m_Graphics->Frame(m_Timer->GetTime() / 1000);
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





