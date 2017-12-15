#include "Camera.h"
#include <iostream>

Camera::Camera(D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation)
{
	float twoPi = D3DX_PI; //handig om een eigen util/math klasse te maken waar twopi al in is gedefineerd

	eye.x = _eye.x;
	eye.y = _eye.y;
	eye.z = _eye.z;

	lookAt.x = _lookAt.x;
	lookAt.y = _lookAt.y;
	lookAt.z = _lookAt.z;

	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;

	translation.x = 0;
	translation.y = 0;
	translation.z = 0;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
}


Camera::~Camera()
{
}

void Camera::SetupView(LPDIRECT3DDEVICE9 _device)
{
	D3DXMATRIXA16 trans;

	D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);
	D3DXMATRIX worldMtrx = trans;
	_device->SetTransform(D3DTS_WORLD, &worldMtrx);

	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;

	if (rotation.y > 2*D3DX_PI)
		rotation.y = 0;
	if (rotation.y < 0)
		rotation.y = 2 * D3DX_PI;

	D3DXMatrixRotationX(&rotX, rotation.x);
	D3DXMatrixRotationY(&rotY, rotation.y);
	D3DXMatrixRotationZ(&rotZ, rotation.z);

	worldMtrx *= rotX *rotY * rotZ;
	_device->SetTransform(D3DTS_WORLD, &worldMtrx);

	D3DXMATRIX viewMtrx;
	D3DXMatrixLookAtLH(&viewMtrx, &eye, &lookAt, &up);
	_device->SetTransform(D3DTS_VIEW, &viewMtrx);

	D3DXMATRIX projectionMtrx;
	D3DXMatrixPerspectiveFovLH(&projectionMtrx, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	_device->SetTransform(D3DTS_PROJECTION, &projectionMtrx);


}

void Camera::LookAt(D3DXVECTOR3 _lookAt)
{
	lookAt = _lookAt;
}

void Camera::Update()
{
	/*
	rotation.x += 0.01f;
	rotation.y += 0.01f;
	rotation.z += 0.01f;
	*/
}

void Camera::MoveTo(D3DXVECTOR3)
{

}

void Camera::Rotate(float x, float y)
{
	rotation.y -= y*2*D3DX_PI/100;	
}

void Camera::MoveLeft()
{
	float speed = 0.30f;
	translation.z -= speed*cos(rotation.y+0.5*D3DX_PI);
	translation.x += speed*sin(rotation.y+ 0.5*D3DX_PI);
}

void Camera::MoveRight()
{
	float speed = 0.30f;
	translation.z -= speed*cos(rotation.y - 0.5*D3DX_PI);
	translation.x += speed*sin(rotation.y - 0.5*D3DX_PI);
}

void Camera::MoveForwards()
{
	float speed = 0.30f;
	translation.z -= speed*cos(rotation.y);
	translation.x += speed*sin(rotation.y);
}

void Camera::MoveBackwards()
{
	float speed = 0.30f;
	translation.z += speed*cos(rotation.y);
	translation.x -= speed*sin(rotation.y);
}

void Camera::MoveUp()
{
	translation.y -= 0.2f;
}

void Camera::MoveDown()
{
	translation.y += 0.2f;
}
