#include "Transform.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"


Transform::Transform()
{
	position = Vector3(0 ,0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1,1,1);
}


Transform::~Transform()
{
}

void Transform::SetupMatrices(Renderer* renderer)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

		D3DXMATRIX worldMtrx;
		D3DXMatrixIdentity(&worldMtrx);

		D3DXMATRIXA16 trans;
		D3DXMatrixTranslation(&trans, position.x, position.y, position.z);

		D3DXMATRIXA16 rotX;
		D3DXMATRIXA16 rotY;
		D3DXMATRIXA16 rotZ;

		D3DXMatrixRotationX(&rotX, rotation.x);
		D3DXMatrixRotationY(&rotY, rotation.y);
		D3DXMatrixRotationZ(&rotZ, rotation.z);

		worldMtrx = trans* rotZ * rotY * rotX;
		//D3DXMatrixScaling(&worldMtrx, scale.x, scale.y, scale.z);

		device->SetTransform(D3DTS_WORLD, &worldMtrx);
	}
}

void Transform::SetupMatrices(Renderer* renderer, Transform origin)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

		Vector3 tempposition = origin.position;
		D3DXMATRIX cameraMtrx, worldMtrx;

		D3DXMATRIXA16 trans;
		D3DXMatrixTranslation(&trans, tempposition.x, tempposition.y, tempposition.z);

		D3DXMATRIXA16 rotX;
		D3DXMATRIXA16 rotY;
		D3DXMATRIXA16 rotZ;

		Vector3 temprotation = origin.rotation;

		D3DXMatrixRotationX(&rotX, temprotation.x);
		D3DXMatrixRotationY(&rotY, temprotation.y);
		D3DXMatrixRotationZ(&rotZ, temprotation.z);

		cameraMtrx = trans* rotZ * rotY * rotX ;

		D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
		D3DXMatrixRotationX(&rotX, rotation.x);
		D3DXMatrixRotationY(&rotY, rotation.y);
		D3DXMatrixRotationZ(&rotZ, rotation.z);
		
		worldMtrx = rotX*rotY*rotZ*trans;
		worldMtrx *= cameraMtrx;

		device->SetTransform(D3DTS_WORLD, &worldMtrx);
	}
}

void Transform::SetupMatricesRotate(Renderer* renderer, Vector3 _rotation)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

		D3DXMATRIX worldMtrx;
		D3DXMatrixIdentity(&worldMtrx);

		D3DXMATRIXA16 rotX;
		D3DXMATRIXA16 rotY;
		D3DXMATRIXA16 rotZ;

		D3DXMatrixRotationX(&rotX, _rotation.x);
		D3DXMatrixRotationY(&rotY, _rotation.y);
		D3DXMatrixRotationZ(&rotZ, _rotation.z);

		worldMtrx = rotZ * rotY * rotX;

		device->SetTransform(D3DTS_WORLD, &worldMtrx);
	}
}

Vector3 Transform::GetPosition()
{
	return position;
}

void Transform::SetPosition(Vector3 _position)
{
	position = _position;
}

Vector3 Transform::GetRotation()
{
	return rotation;
}

void Transform::SetRotation(Vector3 _rotation)
{
	rotation = _rotation;
}

Vector3 Transform::GetScale()
{
	return scale;
}

void Transform::SetScale(Vector3 _scale)
{
	scale = _scale;
}