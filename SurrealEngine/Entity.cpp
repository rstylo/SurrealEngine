#include "Entity.h"
#include "Resource.h"



Entity::Entity(Vector3 _position, Vector3 _rotation)
{
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft

	transform.SetPosition(Vector3(_position.x, _position.y, _position.z));
	transform.SetRotation(Vector3(_rotation.x, _rotation.y, _rotation.z));

}


Entity::~Entity()
{
}

bool Entity::Init(Renderer* renderer)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{

	return true;
}

void Entity::SetupMatrices(Renderer* renderer, Transform origin)						//setup world matrix for the position in with the resources are to pe drawn 
{
	transform.SetupMatrices(renderer, origin);
}
void Entity::Draw(Renderer* renderer)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{
	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		if ((*it)->Init(renderer))												//if the current resource is already initialized
			(*it)->Draw(renderer);											//draw it
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


std::string Entity::GetEntityInfo()			//get information off this entity to save in a txt
{
	std::string entityInfo;
	entityInfo = "entity\n";

	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		//cast resource to mesh
		/*if (Mesh* mesh = dynamic_cast<Mesh*>(*it))
		{
			break;
		}*/
		
	}

	//positie & rotatie of mesh
	Vector3 pos = transform.GetPosition();
	Vector3 rot = transform.GetRotation();

	entityInfo += pos.x;
	entityInfo += "\n";
	entityInfo += pos.y;
	entityInfo += "\n";
	entityInfo += pos.z;
	entityInfo += "\n";

	entityInfo += rot.x;
	entityInfo += "\n";
	entityInfo += rot.y;
	entityInfo += "\n";
	entityInfo += rot.z;
	entityInfo += "\n";

	return entityInfo;
}