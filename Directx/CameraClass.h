#pragma once

#include <DirectxMath.h>
using namespace DirectX;

class CameraClass
{
	//֧�����������ģ�� AIRCRAFT �����ڿռ������˶�,����6�����ɶ�
	// LANDOBJECT ��ĳЩ�ض�������ƶ�
public:
	enum CameraType { LANDOBJECT, AIRCRAFT };

public:
	CameraClass(void);
	CameraClass(const CameraClass&);
	~CameraClass(void);

	void strafe(float units); // l����
	void fly(float units);    // ����
	void walk(float units);   // ǰ��

	void pitch(float angle); // ��תview����ϵright����
	void yaw(float angle);   // ��תup����
	void roll(float angle);  // ��תlook����

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

