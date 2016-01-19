#include "CameraClass.h"


CameraClass::CameraClass(void)
{
	_cameraType = AIRCRAFT;

	_pos   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	_up    = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_look  = XMFLOAT3(0.0f, 0.0f, 1.0f);

}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass(void)
{
}

void CameraClass::Reset()
{
	_pos   = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	_up    = XMFLOAT3(0.0f, 1.0f, 0.0f);
	_look  = XMFLOAT3(0.0f, 0.0f, 1.0f);
}

void CameraClass::getPosition(XMFLOAT3* pos)
{
	*pos = _pos;
}

void CameraClass::setPosition(XMFLOAT3* pos)
{
	_pos = *pos;
}

void CameraClass::getRight(XMFLOAT3* right)
{
	*right = _right;
}

void CameraClass::getUp(XMFLOAT3* up)
{
	*up = _up;
}

void CameraClass::getLook(XMFLOAT3* look)
{
	*look = _look;
}

//���ߣ�����������۲췽����ƶ�
void CameraClass::walk(float units)
{
	XMVECTOR pos = XMLoadFloat3(&_pos);
	
	// ����x,zƽ���ƶ�
	if (_cameraType == LANDOBJECT)
		pos += XMLoadFloat3(&XMFLOAT3(_look.x, 0.0f, _look.z)) * units;

	if (_cameraType == AIRCRAFT)
		pos += XMLoadFloat3(&_look) * units;

	XMStoreFloat3(&_pos, pos);
}

//ɨ�ӣ���ָ���ֹ۲췽�򲻱䣬������right�����һ��ƽ�Ƶ���һ��
void CameraClass::strafe(float units)
{
	XMVECTOR pos = XMLoadFloat3(&_pos);

	// ����x,zƽ���ƶ�
	if (_cameraType == LANDOBJECT)
		pos += XMLoadFloat3(&XMFLOAT3(_right.x, 0.0f, _right.z)) * units;
	
	if (_cameraType == AIRCRAFT)
		pos += XMLoadFloat3(&_right) * units;

	XMStoreFloat3(&_pos, pos);
}

//����ģʽ��������ָ��������up������ƶ�
void CameraClass::fly(float units)
{
	// ����y���ƶ�
	if (_cameraType == LANDOBJECT)
		_pos.y += units;
	
	XMVECTOR pos = XMLoadFloat3(&_pos);

	if (_cameraType == AIRCRAFT)
		pos += XMLoadFloat3(&_up) * units;

	XMStoreFloat3(&_pos, pos);
}

void CameraClass::pitch(float angle)
{
	XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_right), angle);

	// ����right��������תup��look
	XMStoreFloat3(&_up, XMVector3TransformCoord(XMLoadFloat3(&_up), T));
	XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), T));
}

void CameraClass::yaw(float angle)
{
	XMMATRIX T;

	//��LANDOBJECT,��������(0,1,0)��ת��
	if (_cameraType == LANDOBJECT)
		T = XMMatrixRotationY(angle);

	//����aircraft,����up������ת
	if (_cameraType == AIRCRAFT)
		T = XMMatrixRotationAxis(XMLoadFloat3(&_up), angle);

	// ����up����y�ᣬ��תright��look
	XMStoreFloat3(&_right, XMVector3TransformCoord(XMLoadFloat3(&_right), T));
	XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), T));
}

void CameraClass::roll(float angle)
{
	//ֻ��aircraftģʽ����roll��ת
	if (_cameraType == AIRCRAFT)
	{
		XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_look), angle);

		// ����look��������תup��right
		XMStoreFloat3(&_right, XMVector3TransformCoord(XMLoadFloat3(&_right), T));
		XMStoreFloat3(&_up, XMVector3TransformCoord(XMLoadFloat3(&_up), T));
	}
}

void CameraClass::getViewMatrix(XMFLOAT4X4* V)
{
	// ����view�ֲ�����ϵ������ı˴�����
	XMVECTOR look =	XMVector3Normalize(XMLoadFloat3(&_look));  // ��һ��

	XMVECTOR up =	XMVector3Cross(XMLoadFloat3(&_look), XMLoadFloat3(&_right));  // ���
	up = XMVector3Normalize(up);

	XMVECTOR right = XMVector3Cross(XMLoadFloat3(&_up), XMLoadFloat3(&_look));
	right = XMVector3Normalize(right);

	XMVECTOR pos = XMLoadFloat3(&_pos);

	// ����view����:
	float x = -XMVectorGetX(XMVector3Dot(right, pos));  //���dot��[dot, dot, dot, dot]
	float y = -XMVectorGetY(XMVector3Dot(up, pos));
	float z = -XMVectorGetZ(XMVector3Dot(look, pos));

	(*V)(0, 0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
	(*V)(1, 0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
	(*V)(2, 0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
	(*V)(3, 0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}

void CameraClass::setCameraType(CameraType cameraType)
{
	_cameraType = cameraType;
}

