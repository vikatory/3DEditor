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

//行走，沿着摄像机观察方向的移动
void CameraClass::walk(float units)
{
	XMVECTOR pos = XMLoadFloat3(&_pos);
	
	// 仅在x,z平面移动
	if (_cameraType == LANDOBJECT)
		pos += XMLoadFloat3(&XMFLOAT3(_look.x, 0.0f, _look.z)) * units;

	if (_cameraType == AIRCRAFT)
		pos += XMLoadFloat3(&_look) * units;

	XMStoreFloat3(&_pos, pos);
}

//扫视，是指保持观察方向不变，沿向量right方向从一边平移到另一边
void CameraClass::strafe(float units)
{
	XMVECTOR pos = XMLoadFloat3(&_pos);

	// 仅在x,z平面移动
	if (_cameraType == LANDOBJECT)
		pos += XMLoadFloat3(&XMFLOAT3(_right.x, 0.0f, _right.z)) * units;
	
	if (_cameraType == AIRCRAFT)
		pos += XMLoadFloat3(&_right) * units;

	XMStoreFloat3(&_pos, pos);
}

//飞行模式，升降，指沿着向量up方向的移动
void CameraClass::fly(float units)
{
	// 仅在y轴移动
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

	// 绕着right向量，旋转up和look
	XMStoreFloat3(&_up, XMVector3TransformCoord(XMLoadFloat3(&_up), T));
	XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), T));
}

void CameraClass::yaw(float angle)
{
	XMMATRIX T;

	//对LANDOBJECT,总是绕着(0,1,0)旋转。
	if (_cameraType == LANDOBJECT)
		T = XMMatrixRotationY(angle);

	//对于aircraft,绕着up向量旋转
	if (_cameraType == AIRCRAFT)
		T = XMMatrixRotationAxis(XMLoadFloat3(&_up), angle);

	// 绕着up或者y轴，旋转right和look
	XMStoreFloat3(&_right, XMVector3TransformCoord(XMLoadFloat3(&_right), T));
	XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), T));
}

void CameraClass::roll(float angle)
{
	//只对aircraft模式才左roll旋转
	if (_cameraType == AIRCRAFT)
	{
		XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_look), angle);

		// 绕着look向量，旋转up和right
		XMStoreFloat3(&_right, XMVector3TransformCoord(XMLoadFloat3(&_right), T));
		XMStoreFloat3(&_up, XMVector3TransformCoord(XMLoadFloat3(&_up), T));
	}
}

void CameraClass::getViewMatrix(XMFLOAT4X4* V)
{
	// 保持view局部坐标系，各轴的彼此正交
	XMVECTOR look =	XMVector3Normalize(XMLoadFloat3(&_look));  // 归一化

	XMVECTOR up =	XMVector3Cross(XMLoadFloat3(&_look), XMLoadFloat3(&_right));  // 叉乘
	up = XMVector3Normalize(up);

	XMVECTOR right = XMVector3Cross(XMLoadFloat3(&_up), XMLoadFloat3(&_look));
	right = XMVector3Normalize(right);

	XMVECTOR pos = XMLoadFloat3(&_pos);

	// 生成view矩阵:
	float x = -XMVectorGetX(XMVector3Dot(right, pos));  //点积dot，[dot, dot, dot, dot]
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

