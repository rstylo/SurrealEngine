#include "Entity.h"
#include "Resource.h"



Entity::Entity(D3DXVECTOR3 _position, D3DXVECTOR3 _rotation)
{
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft

	transform.SetPosition(Vector3(_position.x, _position.y, _position.z));
	transform.SetRotation(Vector3(_rotation.x, _rotation.y, _rotation.z));

}


Entity::~Entity()
{
}

bool Entity::Init(LPDIRECT3DDEVICE9 device)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{

	return true;
}

void Entity::SetupMatrices(LPDIRECT3DDEVICE9 device)						//setup world matrix for the position in with the resources are to pe drawn 
{
	transform.SetupMatrices(device);										
}
void Entity::Draw(LPDIRECT3DDEVICE9 device)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{

	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		if((*it)->Init(device))												//if the current resource is already initialized
			(*it)->Draw(device);											//draw it
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

