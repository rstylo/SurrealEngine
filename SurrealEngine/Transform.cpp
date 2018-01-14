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

		//D3DXVECTOR3 _position = D3DXVECTOR3(position.x ,position.y, position.z);
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



		worldMtrx = rotX * rotY * rotZ * trans;
		//D3DXMatrixScaling(&worldMtrx, scale.x, scale.y, scale.z);
		
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