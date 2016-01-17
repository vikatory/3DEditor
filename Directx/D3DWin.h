#pragma once

#include <QWidget>

#include <dxgi.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <assert.h>

class QResizeEvent;
class QPaintEvent;

#define safe_release(x)		 { if(x) { (x)->Release(); (x) = 0;	} }

class D3DRenderWidget : public QWidget
{
	Q_OBJECT

public:
	D3DRenderWidget(QWidget *parent = NULL);
	~D3DRenderWidget();

	virtual QPaintEngine* paintEngine() const { return NULL; }

protected:
	virtual void resizeEvent(QResizeEvent *e);
	virtual void paintEvent(QPaintEvent *e);

	bool createDevice();
	void d3dRender();
	void d3dResize();

private:
	UINT					m_4xMsaaQuality;

	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_d3dImmediateContext;
	IDXGISwapChain*			m_swapChain;
	ID3D11Texture2D*		m_depthStencilBuffer;
	ID3D11RenderTargetView*	m_renderTargetView;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT			m_screenViewport;
	bool					m_enable4xMsaa;

	D3D_DRIVER_TYPE			m_d3dDriverType;
};


