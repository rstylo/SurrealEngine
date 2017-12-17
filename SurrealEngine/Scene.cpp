#include "Scene.h"
#include "Terrain.h"
#include "Camera.h"


Scene::Scene(D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, InputHandler* _inputHandler)
{

	id = reinterpret_cast<uint32_t>(this);


	terrain = new Terrain();
	

	AddCamera(0, _eye, _lookAt, D3DXVECTOR3(0,0,0), _inputHandler);										//game camera
	AddCamera(1, D3DXVECTOR3(0, 20, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), _inputHandler);		//dev camera
}


Scene::~Scene()
{
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		delete it->second;
	}
}

uint32_t Scene::GetId()
{
	return id;
}

Camera * Scene::GetCamera(int cam)
{
	return cameras.find(cam)->second;
}

void Scene::SetupTerrain(LPDIRECT3DDEVICE9 _device)
{
	if (terrain != NULL)
	{
		terrain->Init(_device, 100);
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
		cameras[0]->Update(0);
		cameras[1]->Update(1);

		terrain->Draw(_device);
	}
}

void Scene::AddCamera(int cam, D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation, InputHandler* _inputHandler)
{
	if (cameras.find(cam) == cameras.end())
		cameras[cam] = new Camera(_eye, _lookAt, _rotation, _inputHandler);
	else
		printf("camera %d already exists!!", cam);
}
