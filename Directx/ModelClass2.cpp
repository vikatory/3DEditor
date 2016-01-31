#include "ModelClass2.h"


ModelClass2::ModelClass2(void)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

}

ModelClass2::ModelClass2(const ModelClass2 & others)
{

}

ModelClass2::~ModelClass2(void)
{
}

bool ModelClass2::Initialize(ID3D11Device* device, int m, int n, float dx)
{
	bool result;


	// ��ʼ�����㻺��Ͷ�����������.
	result = InitializeBuffers(device, m, n, dx);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass2::Shutdown()
{
	// �ͷŶ������������.
	ShutdownBuffers();

	return;
}

float ModelClass2::getHeight(float x, float z) const
{
	return 0.3f*(z*sinf(0.1f*x) + x*cosf(0.1f*z));
}

void ModelClass2::Render(ID3D11DeviceContext* deviceContext)
{
	// �Ѷ���������������ͼ�ι��ߣ�׼����Ⱦ.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass2::GetIndexCount()
{
	//���������������
	return m_indexCount;
}

bool ModelClass2::InitializeBuffers(ID3D11Device* device, int m, int n, float dx)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	//����õ����������������Ŀ
	//���ȵõ������ε���Ŀ��Ȼ�����3���Ƕ���������Ŀ
	m_vertexCount = m*n;
	m_indexCount = (m - 1)*(n - 1) * 2 * 3;

	// ����������ʱ����.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	float halfWidth = (n - 1)*dx*0.5f;
	float halfDepth = (m - 1)*dx*0.5f;

	for (int i = 0; i < m; ++i)
	{
		float z = halfDepth - i*dx;
		for (int j = 0; j < n; ++j)
		{
			float x = -halfWidth + j*dx;

			// ����õ�zֵ.
			float y = getHeight(x, z);

			vertices[i*n + j].position = XMFLOAT3(x, y, z);

			// ���ݸ߶���������ɫ
			if (y < -10.0f)
				vertices[i*n + j].color = BEACH_SAND;
			else if (y < 5.0f)
				vertices[i*n + j].color = LIGHT_YELLOW_GREEN;
			else if (y < 12.0f)
				vertices[i*n + j].color = DARK_YELLOW_GREEN;
			else if (y < 20.0f)
				vertices[i*n + j].color = DARKBROWN;
			else
				vertices[i*n + j].color = WHITE;
		}
	}

	// ������������.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// ����ÿ��grid������ó�����.
	int k = 0;
	for (int i = 0; i < m - 1; ++i)
	{
		for (int j = 0; j < n - 1; ++j)
		{
			indices[k] = i*n + j;
			indices[k + 1] = i*n + j + 1;
			indices[k + 2] = (i + 1)*n + j;

			indices[k + 3] = (i + 1)*n + j;
			indices[k + 4] = i*n + j + 1;
			indices[k + 5] = (i + 1)*n + j + 1;

			k += 6; //��һ��grid
		}
	}

	// ���ö��㻺������
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// ָ�򱣴涥�����ݵ���ʱ����.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// �������㻺��.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		//HR(result);
		return false;
	}

	// ����������������.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// ָ�����ʱ��������.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// ������������.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		//HR(result);
		return false;
	}

	// �ͷ���ʱ����.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass2::ShutdownBuffers()
{
	// �ͷŶ��㻺��.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// �ͷ���������
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ModelClass2::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// ���ö��㻺���Ⱥ�ƫ��.
	stride = sizeof(VertexType);
	offset = 0;

	//��input assemberl�׶ΰ󶨶��㻺�壬�Ա��ܹ�����Ⱦ
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//��input assemberl�׶ΰ��������壬�Ա��ܹ�����Ⱦ
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// ������Ԫ���壬��Ⱦ�������б�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

