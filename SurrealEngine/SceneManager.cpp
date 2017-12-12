#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"


SceneManager::SceneManager()
{
	Scene* startScene = new Scene(D3DXVECTOR3(0 ,5 ,-5), D3DXVECTOR3(0, 4, 0));
	currentScene = startScene;
}


SceneManager::~SceneManager()
{
	for (auto it = scenes.begin(); it != scenes.end(); it++)
	{
		delete it->second;
	}

	scenes.clear();

	for (auto it = entities.begin(); it != entities.end(); it++)		//iterate door alle entities
	{
		delete it->second;												//verwijder alle values
	}
	entities.clear();													//clear de map

}

void SceneManager::AddScene(Scene* _scene)
{
	if (scenes.find(_scene->GetId()) != scenes.end()) return;
	scenes[_scene->GetId()] = _scene;
	currentScene = _scene;

}

Scene* SceneManager::GetScene(uint32_t _uuid)
{
	if (scenes.find(_uuid) != scenes.end())
		return scenes.find(_uuid)->second;

	return NULL;
}
void SceneManager::Update()
{
}

void SceneManager::Draw(LPDIRECT3DDEVICE9 device, int cam)
{
	if (currentScene != NULL)
	{
		currentScene->SetupMatrices(device, cam);
		currentScene->Draw(device);
	}

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Draw(device);
	}

	
}

void SceneManager::SetupScene(LPDIRECT3DDEVICE9 device)
{
	if (currentScene != NULL)
	{
		
		currentScene->SetupTerrain(device);
		
	}
}

void SceneManager::AddEntity(Entity* _entity)
{
	if (entities.find(_entity->GetId()) != entities.end())				//check of er niet een identieke entity al bestaat, door alleen de key die unqiue is te vergelijken
		return;
	entities[_entity->GetId()] = _entity;								//in geval van geen key zal de enty toegevoegd worden met zijn eigen id als key

}

Entity* SceneManager::GetEntity(uint32_t _uuid)
{
	if (entities.find(_uuid) != entities.end())
		return entities.find(_uuid)->second;

	return NULL;
}

Scene * SceneManager::GetCurrentScene()
{
	return currentScene;
}
