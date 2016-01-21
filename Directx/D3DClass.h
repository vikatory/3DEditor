#pragma once

//���ӳ���ʹ�õ�һЩD3D��
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

//D3D��һЩͷ�ļ�
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

	// vsync:�Ƿ�ֱͬ��. hwnd:���ھ��. fullscreen:�Ƿ�ȫ��. screenDepth:���,Զ��. screenNear:���,����
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

private:
	bool					m_vsync_enabled; //�Ƿ����ô�ֱͬ��
	int						m_videoCardMemory; //�Դ��С
	char					m_videoCardDescription[128]; //�Կ�����
	IDXGISwapChain*			m_swapChain; //����������
	ID3D11Device*			m_device;  //�豸����
	ID3D11DeviceContext*	m_deviceContext; //�豸�����Ķ���
	ID3D11RenderTargetView*	m_renderTargetView; //��ȾĿ����ͼ
	ID3D11Texture2D*		m_depthStencilBuffer;  // A 2D texture interface manages texel data, which is structured memory.
	ID3D11DepthStencilState*m_depthStencilState;  // The depth-stencil-state interface holds a description for depth-stencil state that you can bind to the output-merger stage
	ID3D11DepthStencilView*	m_depthStencilView; //���Ŀ����ͼ
	ID3D11RasterizerState*	m_rasterState; //��Ⱦ״̬
	XMFLOAT4X4				m_projectionMatrix; //ͶӰ����
	XMFLOAT4X4				m_worldMatrix;//��������ϵ����
	XMFLOAT4X4				m_orthoMatrix;//����ͶӰ����
};

