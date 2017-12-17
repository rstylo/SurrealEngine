#include "Scene.h"
#include "Terrain.h"
#include "Camera.h"
#include "Entity.h"


Scene::Scene()
{

	id = reinterpret_cast<uint32_t>(this);


	terrain = new Terrain();
	
	terrain->LoadBMP("map.bmp");

	AddCamera(0, D3DXVECTOR3(50, 200, 50), D3DXVECTOR3(0, 100, 0), D3DXVECTOR3(0, 0, 0));			//game camera
	AddCamera(1, D3DXVECTOR3(-100, 300, -100), D3DXVECTOR3(50, 100, 50), D3DXVECTOR3(0, 0, 0));		//dev camera
}


Scene::~Scene()
{
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		delete it->second;
	}

	for (auto it = entities.begin(); it != entities.end(); it++)		//iterate door alle entities
	{
		delete it->second;												//verwijder alle values
	}
	entities.clear();													//clear de map

	if (terrain != NULL)
	{
		delete terrain;
	}
}

uint32_t Scene::GetId()
{
	return id;
}

void Scene::SetupTerrain(LPDIRECT3DDEVICE9 _device)
{
	if (terrain != NULL)
	{
		terrain->Init(_device, 100, 100);
	}

}

void Scene::SetupMatrices(LPDIRECT3DDEVICE9 _device, int cam)
{
	auto it = cameras.find(cam);
	if (it != cameras.end() && it->second != NULL)
	{
		it->second->SetupView(_device);
	}
	else
	{
		printf("failed displaying camera view for cam: %d \n", &cam);
	}

}

void Scene::Draw(LPDIRECT3DDEVICE9 _device)
{
	if (terrain != NULL)
	{
		cameras[0]->Update();					//hoort hier niet
		cameras[1]->Update();					//hoort hier niet

		terrain->Draw(_device);
	}

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Draw(_device);
	}
}

void Scene::AddCamera(int cam, D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation)
{
	if (cameras.find(cam) == cameras.end())
		cameras[cam] = new Camera(_eye, _lookAt, _rotation);
	else
		printf("camera %d already exists!! \n", cam);
}

void Scene::AddEntity(Entity* _entity)
{
	
	if (entities.find(_entity->GetId()) != entities.end()) {				//check of er niet een identieke entity al bestaat, door alleen de key die unqiue is te vergelijken
		printf("entity %d already exists!! \n", _entity->GetId());
		return;
	}

	entities[_entity->GetId()] = _entity;								//in geval van geen key zal de enty toegevoegd worden met zijn eigen id als key
	printf("added entity %d... \n", _entity->GetId());

}

Entity* Scene::GetEntity(uint32_t _uuid)
{
	if (entities.find(_uuid) != entities.end())
		return entities.find(_uuid)->second;

	return NULL;
}