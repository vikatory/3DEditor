#pragma once
#include <d3d11.h>
#include <DirectxMath.h>

#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

////#include <dxerr.h>
//#include <DxErr.h>
//#include <cassert>
//
//
////一个简单的错误检测宏
//#if defined(DEBUG) | defined(_DEBUG)
//#ifndef HR
//#define HR(x)												   \
//	{                                                          \
//		HRESULT hr = (x);                                      \
//		if(FAILED(hr))                                         \
//		{                                                      \
//			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
//		}                                                      \
//	}
//#endif
//
//#else
//#ifndef HR
//#define HR(x) (x)
//#endif
//#endif



//定义一些常用颜色
const DirectX::XMFLOAT4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const DirectX::XMFLOAT4 BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const DirectX::XMFLOAT4 RED(1.0f, 0.0f, 0.0f, 1.0f);
const DirectX::XMFLOAT4 GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const DirectX::XMFLOAT4 BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const DirectX::XMFLOAT4 YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const DirectX::XMFLOAT4 CYAN(0.0f, 1.0f, 1.0f, 1.0f); //蓝绿色
const DirectX::XMFLOAT4 MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);//洋红色

const DirectX::XMFLOAT4 BEACH_SAND(1.0f, 0.96f, 0.62f, 1.0f);
const DirectX::XMFLOAT4 LIGHT_YELLOW_GREEN(0.48f, 0.77f, 0.46f, 1.0f);
const DirectX::XMFLOAT4 DARK_YELLOW_GREEN(0.1f, 0.48f, 0.19f, 1.0f);
const DirectX::XMFLOAT4 DARKBROWN(0.45f, 0.39f, 0.34f, 1.0f);
