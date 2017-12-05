#include "EntityManager.h"
#include "Entity.h"
#include "GameEntity.h"
#include <d3dx9.h>


EntityManager::EntityManager() : Manager("EntityManager") {}

EntityManager::~EntityManager() {}

void EntityManager::Init(LPDIRECT3DDEVICE9 device)
{
	//maak entity aan om te renderen
	game = new GameEntity();
	game->Init(device);
	game->SetMesh("tiger.x");
}

Entity* EntityManager::GetEntity(uint32_t _uuid)
{
	if (entities.find(_uuid) != entities.end())
		return entities.find(_uuid)->second;
	return NULL;
}

void EntityManager::DrawEntities()
{
	game->Draw();
}