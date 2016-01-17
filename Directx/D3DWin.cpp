#include "D3DWin.h"

#include <QTimer>

D3DRenderWidget::D3DRenderWidget(QWidget *parent)
	: QWidget(parent),
	m_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
	m_enable4xMsaa(false),
	m_4xMsaaQuality(0),
	m_d3dDevice(0),
	m_d3dImmediateContext(0),
	m_swapChain(0),
	m_depthStencilBuffer(0),
	m_renderTargetView(0),
	m_depthStencilView(0)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));

	ZeroMemory(&m_screenViewport, sizeof(D3D11_VIEWPORT));

	createDevice();
}

D3DRenderWidget::~D3DRenderWidget()
{
	safe_release(m_renderTargetView);
	safe_release(m_depthStencilView);
	safe_release(m_swapChain);
	safe_release(m_depthStencilBuffer);

	if (m_d3dImmediateContext)
		m_d3dImmediateContext->ClearState();

	safe_release(m_d3dImmediateContext);
	safe_release(m_d3dDevice);
}

void D3DRenderWidget::resizeEvent(QResizeEvent *e)
{
	d3dResize();
}

void D3DRenderWidget::paintEvent(QPaintEvent *e)
{
	d3dRender();
}

bool D3DRenderWidget::createDevice()
{
	HRESULT re;  // 函数返回值, HRESULT 是一种简单的数据类型，通常被属性和 ATL 用作返回值。
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;  // Direct3D 设备的功能级别目标
	HRESULT hr = D3D11CreateDevice(
		0,
		m_d3dDriverType,
		0,
		createDeviceFlags,
		0,
		0,
		D3D11_SDK_VERSION,
		&m_d3dDevice,
		&featureLevel,
		&m_d3dImmediateContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	re = m_d3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality);
	if (FAILED(re))	return false;

	assert(m_4xMsaaQuality > 0);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = width();
	sd.BufferDesc.Height = height();
	sd.BufferDesc.RefreshRate.Numerator = 60;  // 分子
	sd.BufferDesc.RefreshRate.Denominator = 1;  // 分母
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (m_enable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = (HWND)winId();
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	IDXGIDevice* dxgiDevice = 0;
	re = m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	if (FAILED(re))	return false;

	IDXGIAdapter* dxgiAdapter = 0;
	re = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	if (FAILED(re))	return false;

	IDXGIFactory* dxgiFactory = 0;
	re = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
	if (FAILED(re))	return false;

	re = dxgiFactory->CreateSwapChain(m_d3dDevice, &sd, &m_swapChain);
	if (FAILED(re))	return false;

	safe_release(dxgiDevice);
	safe_release(dxgiAdapter);
	safe_release(dxgiFactory);

	return true;
}

void D3DRenderWidget::d3dRender()
{
	static float blue[4] = { 0.69f, 0.77f, 0.87f, 1.0f };

	assert(m_d3dImmediateContext);
	assert(m_swapChain);

	m_d3dImmediateContext->ClearRenderTargetView(m_renderTargetView, &blue[0]);
	m_d3dImmediateContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_swapChain->Present(0, 0);
}

void D3DRenderWidget::d3dResize()
{
	assert(m_d3dImmediateContext);
	assert(m_d3dDevice);
	assert(m_swapChain);

	safe_release(m_renderTargetView);
	safe_release(m_depthStencilView);
	safe_release(m_depthStencilBuffer);

	m_swapChain->ResizeBuffers(1, width(), height(), DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	m_d3dDevice->CreateRenderTargetView(backBuffer, 0, &m_renderTargetView);
	safe_release(backBuffer);

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = width();
	depthStencilDesc.Height = height();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (m_enable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	m_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &m_depthStencilBuffer);
	m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView);

	m_d3dImmediateContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	m_screenViewport.TopLeftX = 0;
	m_screenViewport.TopLeftY = 0;
	m_screenViewport.Width = static_cast<float>(width());
	m_screenViewport.Height = static_cast<float>(height());
	m_screenViewport.MinDepth = 0.0f;
	m_screenViewport.MaxDepth = 1.0f;

	m_d3dImmediateContext->RSSetViewports(1, &m_screenViewport);
}





