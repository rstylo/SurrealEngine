#include "Entity.h"
#include "Resource.h"



Entity::Entity(D3DXVECTOR3 _position, D3DXVECTOR3 _rotation)
{
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft

	position.x = _position.x;
	position.y = _position.y;
	position.z = _position.z;

	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;

}


Entity::~Entity()
{
}

bool Entity::Init(LPDIRECT3DDEVICE9 device)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{

	return true;
}

void Entity::SetupMatrices(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX worldMtrx;
	//D3DXMatrixIdentity(&worldMtrx);

	D3DXMATRIXA16 trans;

	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);

	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;

	D3DXMatrixRotationX(&rotX, rotation.x);
	D3DXMatrixRotationY(&rotY, rotation.y);
	D3DXMatrixRotationZ(&rotZ, rotation.z);

	worldMtrx = rotX * rotY * rotZ * trans;
	device->SetTransform(D3DTS_WORLD, &worldMtrx);
}

void Entity::Draw(LPDIRECT3DDEVICE9 device)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{

	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		if ((*it)->Init(device))
		{
			(*it)->Draw(device);
		}
		else 
		{
			printf("resource %d @ entity %d was not Initialized \n", (*it)->GetId(), GetId());
		}
	}
}

void Entity::AddResource(Resource* _resource)				
{
	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		if ((*it) == _resource)
		{
			return;
		}
	}

	myResources.push_back(_resource);
}


uint32_t Entity::GetId()							
{
	return id;														
}

