#include "GraphicsClass.h"


GraphicsClass::GraphicsClass(void)
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_AxisModel = 0;
	m_ColorShader = 0;
	m_WaterModel = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass&)
{

}
GraphicsClass::~GraphicsClass(void)
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//��������Ѿ����ڣ����ͷŵ�����
	Shutdown();

	// ����һ��D3DClass����.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// ����D3DClass��ʼ������
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	//�������������
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// ���������λ��.
	XMFLOAT3 campos = XMFLOAT3(8.0f, 3.0f, -20.0f);
	m_Camera->setPosition(&campos);

	// ����ģ�Ͷ���.
	m_Model = new ModelClass2;
	if (!m_Model)
	{
		return false;
	}

	// ��ʼ��ģ�Ͷ���.
	result = m_Model->Initialize(m_D3D->GetDevice(), 300, 300, 1.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// �����Ὠģ�Ͷ���.
	m_AxisModel = new AxisModelClass;
	if (!m_AxisModel)
	{
		return false;
	}
	// ��ʼ��������ģ�Ͷ���.
	result = m_AxisModel->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the axis model object.", L"Error", MB_OK);
		return false;
	}

	// ����ˮģ�Ͷ���.
	m_WaterModel = new WaterModelClass;
	if (!m_WaterModel)
	{
		return false;
	}

	// ��ʼ��ˮģ�Ͷ���.
	result = m_WaterModel->Initialize(m_D3D->GetDevice(), 257, 257, 0.5f, 0.03f, 3.25f, 0.4f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	// ����shader����
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// ��ʼ��shader����
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// �ͷ�shader����.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// �ͷ�ģ�Ͷ���.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// �ͷ�������ģ�Ͷ���.
	if (m_AxisModel)
	{
		m_AxisModel->Shutdown();
		delete m_AxisModel;
		m_AxisModel = 0;
	}

	// �ͷ�ˮģ�Ͷ���.
	if (m_WaterModel)
	{
		m_WaterModel->Shutdown();
		delete m_WaterModel;
		m_WaterModel = 0;
	}

	// �ͷ����������
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//����m_D3D����
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(float dt)
{
	bool result;


	// ����Render��������Ⱦ3D����
	// Render��GraphicsClass��˽�к���.
	result = Render(dt);
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float dt)
{

	XMFLOAT4X4 viewMatrix, projectionMatrix, worldMatrix;
	bool result;


	// ����framebuffer��ɫ
	m_D3D->BeginScene(0.3608f, 0.3608f, 0.3608f, 1.0f);

	// �õ�3������.
	m_Camera->getViewMatrix(&viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//����Ϊʵ�����ģʽ
	m_D3D->SetFillMode(D3D11_FILL_SOLID);

	m_AxisModel->Render(m_D3D->GetDeviceContext());
	// ��shader��Ⱦ.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_AxisModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}
	// ��ģ�Ͷ�����������������ߣ�׼����Ⱦ.
	m_Model->Render(m_D3D->GetDeviceContext());

	// ��shader��Ⱦ.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	static float t_base = 0.0f;
	static float total_time = 0.0f;
	total_time += dt;
	if (total_time - t_base >= 0.25f)
	{
		t_base += 0.25f;

		int i = 5 + rand() % 250;
		int j = 5 + rand() % 250;

		//�õ�1��2֮���һ��������
		float r = 1.0 + (float)(rand()) / (float)RAND_MAX*(2.0 - 1.0);

		m_WaterModel->disturb(i, j, r);
	}

	m_WaterModel->update(m_D3D->GetDeviceContext(), dt);
	//�����߿�ģʽ
	m_D3D->SetFillMode(D3D11_FILL_WIREFRAME);
	// ��ģ�Ͷ�����������������ߣ�׼����Ⱦ.
	m_WaterModel->Render(m_D3D->GetDeviceContext());

	// ��shader��Ⱦ.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	//��framebuffer�е�ͼ��present����Ļ��.
	m_D3D->EndScene();

	return true;
}