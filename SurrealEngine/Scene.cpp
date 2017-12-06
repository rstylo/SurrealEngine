#include "Scene.h"



Scene::Scene(D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt)
{
	//unique id 

	id = reinterpret_cast<uint32_t>(this);
	//voor nu via de scene, starks via een cameras obj?
	eye.x = _eye.x;
	eye.y = _eye.y;
	eye.z = _eye.z;

	//voor nu via de scene, straks via een camera obj??
	lookAt.x = _lookAt.x;
	lookAt.y = _lookAt.y;
	lookAt.z = _lookAt.z;

	up.x = 0.0f;
	up.x = 1.0f;
	up.z = 0.0f;

	angle = 0.0f;
}


Scene::~Scene()
{

}

uint32_t Scene::GetId()
{
	return id;
}

void Scene::SetupMatrices(LPDIRECT3DDEVICE9 device)
{
	//world->setup();
	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;
	
	angle+=0.02f;

	D3DXMatrixRotationX(&rotX, angle);
	D3DXMatrixRotationY(&rotY, angle);
	D3DXMatrixRotationZ(&rotZ, angle);

	world = rotX * rotZ;
	device->SetTransform(D3DTS_WORLD, &world);

	
	//camera->setup();
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &eye, &lookAt, &up);

	device->SetTransform(D3DTS_VIEW, &matView);
	
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);

}

