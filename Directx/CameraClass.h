#pragma once

#include <DirectxMath.h>
using namespace DirectX;

class CameraClass
{
	//支持两种摄像机模型 AIRCRAFT 允许在空间自由运动,具有6个自由度
	// LANDOBJECT 沿某些特定轴进行移动
public:
	enum CameraType { LANDOBJECT, AIRCRAFT };

public:
	CameraClass(void);
	CameraClass(const CameraClass&);
	~CameraClass(void);

	void strafe(float units); // l左右
	void fly(float units);    // 上下
	void walk(float units);   // 前后

	void pitch(float angle); // 旋转view坐标系right向量
	void yaw(float angle);   // 旋转up向量
	void roll(float angle);  // 旋转look向量

	void getViewMatrix(XMFLOAT4X4* V);
	void setCameraType(CameraType cameraType);
	void getPosition(XMFLOAT3* pos);
	void setPosition(XMFLOAT3* pos);

	void getRight(XMFLOAT3* right);
	void getUp(XMFLOAT3* up);
	void getLook(XMFLOAT3* look);
	void Reset();
private:
	CameraType  _cameraType;
	XMFLOAT3 _right;
	XMFLOAT3 _up;
	XMFLOAT3 _look;
	XMFLOAT3 _pos;

};

