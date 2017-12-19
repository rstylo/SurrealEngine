#include "Scene.h"
#include "Terrain.h"
#include "Camera.h"
#include "Entity.h"
#include "Skybox.h"

Scene::Scene()
{

	id = reinterpret_cast<uint32_t>(this);


	terrain = new Terrain();
	skybox = new Skybox();
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
		terrain = NULL;
	}

	if (skybox != NULL)
	{
		delete skybox;
		skybox = NULL;
	}
}

uint32_t Scene::GetId()
{
	return id;
}

void Scene::SetupTerrain(LPDIRECT3DDEVICE9 _device)
{
		
		if (skybox != NULL)
		{

			skybox->Init(_device, CurrentDirectory("skybox.jpg"));
		}

		if (terrain != NULL)
		{
			terrain->InitWithTexture(_device, 100, "map1.bmp", 100, "texture3.jpg");
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

void Scene::SetupLight(LPDIRECT3DDEVICE9 _device)
{
	D3DMATERIAL9 material;
	//
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Ambient.r = 1.0f;
	material.Diffuse.g = material.Ambient.g = 1.0f;
	material.Diffuse.b = material.Ambient.b = 1.0f;
	material.Diffuse.a = material.Ambient.a = 1.0f;
	_device->SetMaterial(&material);

	//directional light
	D3DXVECTOR3 direction;
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 0.5f;
	light.Diffuse.g = 0.5f;
	light.Diffuse.b = 0.5f;
	direction = D3DXVECTOR3(-100.0f,-1000.0f,-100.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &direction);
	light.Range = 100.0f;
	
	_device->SetLight(0, &light);
}

void Scene::Draw(LPDIRECT3DDEVICE9 _device)
{
	if (skybox != NULL)
	{
		skybox->Draw(_device);
	}

	if (terrain != NULL)
	{
		terrain->Draw(_device);
	}



	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Draw(_device);
	}

	
}

void Scene::AddCamera(int cam, D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation, D3DXVECTOR3 _position, HWND* _hwnd, InputHandler* _inputHandler)
{
	if (cameras.find(cam) == cameras.end())
		cameras[cam] = new Camera(_eye, _lookAt, _rotation, _position, _hwnd, _inputHandler);
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

std::string Scene::CurrentDirectory(std::string str)
{
	char dir[MAX_PATH + 1];
	GetCurrentDirectoryA(sizeof(dir), dir); // **** win32 specific ****
	return dir + str;
}