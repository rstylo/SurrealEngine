#include "Entity.h"
//#include "Resource.h"
#include "Resource.h"



Entity::Entity(float x, float y, float z)
{
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft

	position.x = x;
	position.y = y;
	position.z = z;
}


Entity::~Entity()
{
}

void Entity::Draw(LPDIRECT3DDEVICE9 device)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{
	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		(*it)->Draw();
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
		else 
		{
			myResources.push_back(_resource);
		}
	}
}
void Entity::Update()
{

}
uint32_t Entity::GetId()							
{
	return id;														
}

