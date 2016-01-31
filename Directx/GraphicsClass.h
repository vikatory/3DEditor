#pragma once

#include <windows.h>
#include <cstdlib>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "modelclass2.h"
#include "AxisModelClass.h"
#include "colorshaderclass.h"
#include "WaterModelClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN   = false;	//�Ƿ�ȫ��
const bool VSYNC_ENABLED = true;	//�Ƿ�ֱͬ��
const float SCREEN_DEPTH = 1000.0f;	//��ȣ�Զ��
const float SCREEN_NEAR  = 0.1f;	//��ȣ�����

class GraphicsClass
{
public:
	GraphicsClass(void);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass(void);
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown();
	bool Frame(float);
	CameraClass* m_Camera;//��Ϊpublic��������SystemClass�п���
	WaterModelClass* m_WaterModel;
private:
	bool Render(float);

	//����һ��D3DClass���Ա����
	D3DClass* m_D3D;

	ModelClass2* m_Model;
	AxisModelClass* m_AxisModel;
	ColorShaderClass* m_ColorShader;
};

