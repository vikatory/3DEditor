#pragma once

//链接程序使用的一些D3D库
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

//D3D的一些头文件
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectxMath.h>

using namespace DirectX;

class D3DClass
{
public:
	D3DClass(void);
	D3DClass(const D3DClass&);
	~D3DClass(void);

	// vsync:是否垂直同步. hwnd:窗口句柄. fullscreen:是否全屏. screenDepth:深度,远点. screenNear:深度,近点
	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMFLOAT4X4&);
	void GetWorldMatrix(XMFLOAT4X4&);
	void GetOrthoMatrix(XMFLOAT4X4&);

	void GetVideoCardInfo(char*, int&);
	bool SetFillMode(D3D11_FILL_MODE);

private:
	bool					m_vsync_enabled; //是否启用垂直同步
	int						m_videoCardMemory; //显存大小
	char					m_videoCardDescription[128]; //显卡名字
	IDXGISwapChain*			m_swapChain; //交换链对象
	ID3D11Device*			m_device;  //设备对象
	ID3D11DeviceContext*	m_deviceContext; //设备上下文对象
	ID3D11RenderTargetView*	m_renderTargetView; //渲染目标视图
	ID3D11Texture2D*		m_depthStencilBuffer;  // A 2D texture interface manages texel data, which is structured memory.
	ID3D11DepthStencilState*m_depthStencilState;  // The depth-stencil-state interface holds a description for depth-stencil state that you can bind to the output-merger stage
	ID3D11DepthStencilView*	m_depthStencilView; //深度目标视图
	ID3D11RasterizerState*	m_rasterState; //渲染状态
	XMFLOAT4X4				m_projectionMatrix; //投影矩阵
	XMFLOAT4X4				m_worldMatrix;//世界坐标系矩阵
	XMFLOAT4X4				m_orthoMatrix;//正交投影矩阵
};

