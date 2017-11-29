#include "EntityManager.h"
#include "Entity.h"


EntityManager::EntityManager()
	:Manager("EntityManager")											//constructor van pase klasse oproepen
{
}


EntityManager::~EntityManager()
{
	for (auto it = entities.begin(); it != entities.end(); it++)		//iterate door alle entities
	{
		delete it->second;												//verwijder alle values
	}
	entities.clear();													//clear de map
}

void EntityManager::AddEntity(Entity* _entity)
{
	if (entities.find(_entity->GetId()) != entities.end())				//check of er niet een identieke entity al bestaat, door alleen de key die unqiue is te vergelijken
		return;
	entities[_entity->GetId()] = _entity;								//in geval van geen key zal de enty toegevoegd worden met zijn eigen id als key

}

Entity* EntityManager::GetEntity(uint32_t _uuid)
{
	if (entities.find(_uuid) != entities.end())
		return entities.find(_uuid)->second;

	return NULL;
}
void EntityManager::Update()
{
}

void EntityManager::Draw()
{
	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Draw();											
	}
}