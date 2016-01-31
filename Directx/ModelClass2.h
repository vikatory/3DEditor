#pragma once

#include <d3d11.h>
#include <DirectxMath.h>
#include "common.h"
using namespace DirectX;

class ModelClass2
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ModelClass2(void);
	ModelClass2(const ModelClass2 &);

	~ModelClass2(void);
	bool Initialize(ID3D11Device*, int, int, float);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	//根据顶点的x值和z值，计算出y值
	float getHeight(float x, float z)const;

private:
	bool InitializeBuffers(ID3D11Device*, int, int, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	//顶点缓冲和顶点索引缓冲
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

};

