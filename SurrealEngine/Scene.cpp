#include "Scene.h"
#include "Entity.h"
#include "GameEntity.h"
#include <d3dx9.h>
#include "Terrain.h"


Scene::Scene() {}

Scene::~Scene() {}

void Scene::Init(LPDIRECT3DDEVICE9 device)
{
	//Make an game entity for test
	game = new GameEntity();
	game->Init(device);
	game->SetMesh("tiger.x");

	//Generate Terrain
	terrain = new Terrain();
	terrain->LoadBMP("map.bmp");

}

Entity* Scene::GetEntity(uint32_t _uuid)
{
	if (entities.find(_uuid) != entities.end())
		return entities.find(_uuid)->second;
	return NULL;
}

void Scene::DrawEntities()
{
	game->Draw();
}