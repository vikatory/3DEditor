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
const bool FULL_SCREEN   = false;	//是否全屏
const bool VSYNC_ENABLED = true;	//是否垂直同步
const float SCREEN_DEPTH = 1000.0f;	//深度，远点
const float SCREEN_NEAR  = 0.1f;	//深度，近点

class GraphicsClass
{
public:
	GraphicsClass(void);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass(void);
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown();
	bool Frame(float);
	CameraClass* m_Camera;//设为public，便于在SystemClass中控制
	WaterModelClass* m_WaterModel;
private:
	bool Render(float);

	//定义一个D3DClass类成员变量
	D3DClass* m_D3D;

	ModelClass2* m_Model;
	AxisModelClass* m_AxisModel;
	ColorShaderClass* m_ColorShader;
};

