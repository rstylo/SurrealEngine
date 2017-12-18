#include "Scene.h"
#include "Terrain.h"
#include "Camera.h"
#include "Entity.h"


Scene::Scene()
{

	id = reinterpret_cast<uint32_t>(this);


	terrain = new Terrain();
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
		terrain->InitWithTexture(_device, 100, "map.bmp", 100,"texture.jpg");
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


		terrain->Draw(_device);
	}

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Draw(_device);
	}
}

void Scene::AddCamera(int cam, D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation, D3DXVECTOR3 _position, InputHandler* _inputHandler)
{
	if (cameras.find(cam) == cameras.end())
		cameras[cam] = new Camera(_eye, _lookAt, _rotation, _position, _inputHandler);
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

void Scene::Update()
{
	cameras[0]->Update();					//hoort hier niet
	cameras[1]->Update();					//hoort hier niet
}