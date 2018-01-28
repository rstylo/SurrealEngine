#include "Entity.h"
#include "Resource.h"
#include "Mesh.h"



Entity::Entity(Vector3 _position, Vector3 _rotation)
{
	//! initialisation of private variable, position, rotation and identity
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft

	transform.SetPosition(Vector3(_position.x, _position.y, _position.z));
	transform.SetRotation(Vector3(_rotation.x, _rotation.y, _rotation.z));

}


Entity::~Entity()
{
}

bool Entity::Init(Renderer* renderer)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{
	//! is empty
	return true;
}

void Entity::SetupMatrices(Renderer* renderer, Transform origin)		//setup world matrix for the position in with the resources are to pe drawn 
{
	//! calls transform's SetupMatrices
	transform.SetupMatrices(renderer, origin);
}
void Entity::Draw(Renderer* renderer)									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{
	//! draws all resource this entity holds, initialising them first if needed
	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		if ((*it)->Init(renderer))											//if the current resource is already initialized
			(*it)->Draw(renderer);											//draw it
	}
}

void Entity::AddResource(Resource* _resource)
{
	//! adds a resource that the entity will draw 
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
	//! returns this entities id
	return id;
}


std::string Entity::GetEntityInfo()			//get information off this entity to save
{

	//! returns this entytie information for saving the scene
	std::string entityInfo;
	entityInfo = "entity\n";
	//name van mesh
	for (auto it = myResources.begin(); it != myResources.end(); it++)
	{
		//get mesh name by casting the resource to mesh
		
		if (Mesh* mesh = dynamic_cast<Mesh*>(*it))
		{
			entityInfo += mesh->GetMeshName();
			entityInfo += "\n";
			break;
		}
		
	}

	//positie en rotatie van mesh
	Vector3 pos = transform.GetPosition();
	Vector3 rot = transform.GetRotation();

	entityInfo += std::to_string(pos.x);
	entityInfo += "\n";
	entityInfo += std::to_string(pos.y);
	entityInfo += "\n";
	entityInfo += std::to_string(pos.z);
	entityInfo += "\n";

	entityInfo += std::to_string(rot.x);
	entityInfo += "\n";
	entityInfo += std::to_string(rot.y);
	entityInfo += "\n";
	entityInfo += std::to_string(rot.z);
	entityInfo += "\n";
	
	return entityInfo;
}