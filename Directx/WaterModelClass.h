#pragma once

#include <d3d11.h>
#include <DirectxMath.h>
#include <vector>
#include "common.h"
using namespace DirectX;

using namespace std;

class WaterModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
public:
	WaterModelClass(void);
	WaterModelClass(const WaterModelClass&);
	~WaterModelClass(void);

	bool Initialize(ID3D11Device*, int, int, float, float, float, float);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	bool update(ID3D11DeviceContext*, float);
	void disturb(int, int, float);

private:
	bool InitializeBuffers(ID3D11Device*, int, int, float, float, float, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	//顶点缓冲和顶点索引缓冲
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	//二维网格的行数、列数
	int m_NumRows, m_NumCols;

	// 欲计算的模拟常量.
	float mK1;
	float mK2;
	float mK3;

	float mTimeStep;
	float mSpatialStep;

	XMFLOAT3* mPrevSolution;
	XMFLOAT3* mCurrSolution;

	//顶点临时缓冲
	VertexType* vertices;
};

