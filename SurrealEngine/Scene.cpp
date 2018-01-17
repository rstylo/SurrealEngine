#include "Scene.h"
#include "Terrain.h"
#include "Camera.h"
#include "Entity.h"
#include "Skybox.h"

Scene::Scene(std::string _name)
	:name(_name)
{

	id = reinterpret_cast<uint32_t>(this);

	skybox = new Skybox();

	terrain = new Terrain();
	
	originTransform.SetPosition(Vector3(0, 0, 0));
	originTransform.SetRotation(Vector3(0, 0, 0));
		
}


Scene::~Scene()
{
	for (auto it = cameras.begin(); it != cameras.end(); it++)
	{
		delete it->second;
	}
	cameras.clear();

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

bool Scene::InitEntities(Renderer* renderer)
{
	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		if (it->second->Init(renderer) == false)
		{
			/*if(skybox->Init(renderer, "skybox.jpg"))
				skybox->Create();*/
		}
	}

	return true;
}


void Scene::InvalidateObjects()
{
	if(skybox != NULL)
		skybox->Invalidate();
	if(terrain != NULL)
		terrain->Invalidate();

}

void Scene::SetupSkybox(Renderer* renderer)
{		
	if (skybox != NULL)
	{
		if (skybox->Init(renderer))
			skybox->Create();
	}
}

void Scene::SetupTerrain(Renderer* renderer)
{

	if (terrain != NULL)
	{
		
		terrain->InitWithTexture(renderer);
	}

}

void Scene::SetupMatrices(Renderer* renderer, int cam)
{
	originTransform.SetupMatrices(renderer);
	if (cameras[cam] != NULL) {
		originTransform.SetPosition(cameras[cam]->GetPosition());
		originTransform.SetRotation(cameras[cam]->GetRotation());
	}
}

void Scene::SetupView(Renderer* renderer, int cam)
{
	auto it = cameras.find(cam);

	if (it != cameras.end() && it->second != NULL)
	{
		it->second->SetupView(renderer);
	}
	else
	{
		printf("failed displaying camera view for cam: %d \n", &cam);
	}
}

void Scene::SetupLight(Renderer* renderer)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 _device = *dxrenderer->GetDevice();
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

		direction = D3DXVECTOR3(-100.0f, -1000.0f, -100.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &direction);
		light.Range = 100.0f;

		_device->SetLight(0, &light);
	}
}

void Scene::Draw(Renderer* renderer)
{
	if (skybox != NULL)
	{
		skybox->SetupMatrices(renderer, originTransform);
		skybox->Draw(renderer);
	}

	if (terrain != NULL)
	{
		terrain->SetupMatrices(renderer, originTransform);
		terrain->Draw(renderer);
	}

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->SetupMatrices(renderer, originTransform);
		it->second->Draw(renderer);
	}
}

void Scene::AddCamera(int cam, Vector3 _rotation, Vector3 _position, HWND* _hwnd, InputHandler* _inputHandler)
{
	if (cameras.find(cam) == cameras.end())
		cameras[cam] = new Camera(_rotation, _position, _hwnd, _inputHandler);
	else
		printf("camera %d already exists!! \n", cam);
}

Camera* Scene::GetCamera(int cam)
{
	if (cameras.find(cam) != cameras.end())
		return cameras.find(cam)->second;

	return NULL;
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

	std::cout << " could not find entity " << _uuid << std::endl;
	return NULL;
}

void Scene::RemoveEntity(uint32_t _uuid)
{
	if (entities.find(_uuid) != entities.end())
		delete entities.find(_uuid)->second;
	else
		std::cout << " could not find entity "<< _uuid << std::endl;
}

void Scene::MoveTerrainTo(Vector3 position, Vector3 rotation)
{
	terrain->transform.SetPosition(position);
	terrain->transform.SetRotation(rotation);
}

void Scene::MoveEntityTo(uint32_t _uuid, Vector3 position, Vector3 rotation)
{
	GetEntity(_uuid)->transform.SetPosition(position);
	GetEntity(_uuid)->transform.SetRotation(rotation);
}

void Scene::Update()
{
	if(cameras[0] != NULL)
		cameras[0]->Update();					//hoort hier niet
	if (cameras[1] != NULL)
		cameras[1]->Update();					//hoort hier niet
	if(skybox!=NULL && cameras[0] != NULL)
		skybox->Update(cameras[0]->GetPosition());
}

std::string Scene::CurrentDirectory(std::string str)
{
	char dir[MAX_PATH + 1];
	GetCurrentDirectoryA(sizeof(dir), dir); // **** win32 specific ****
	return dir + str;
}

std::string Scene::GetName()
{
	return name;
}

void Scene::CreateEntityWithMesh(Vector3 _position, Vector3 _rotation, Resource* mesh)
{

	Entity* entity1 = new Entity(_position, _rotation);
	AddEntity(entity1);

	entity1->AddResource(mesh);
}

bool Scene::CreateTerrainWithTexture(std::string map, std::string texture)
{
	if (terrain == NULL)
	{
		terrain = new Terrain();
		terrain->SetMapAndTexture(map, texture);
		return true;
	}
	else
	{
		terrain->SetMapAndTexture(map, texture);
		printf("terrain already exists in scene, map and texture have been changed!! \n");
		return false;
	}

	
}


bool Scene::SetSkyboxTexture(std::string texture)
{
	if (skybox == NULL)
	{
		skybox = new Skybox();
		skybox->SetTexture(texture);
		return true;
	}
	else
	{
		skybox->SetTexture(texture);
		printf("skybox already exists in scene, texture have been changed!! \n");
		return false;
	}
}

//get information of the scene to save to a file
std::string Scene::GetSceneInfo()
{
	std::string sceneInfo;
	sceneInfo += "scene\n";
	sceneInfo += GetName();

	sceneInfo += "terrain\n";
	sceneInfo += terrain->GetMapFileName();
	sceneInfo += terrain->GetTextureName();

	for (auto it = entities.begin(); it != entities.end(); it++)		//iterate door alle entities
	{
		sceneInfo += "entity\n";
		sceneInfo += it->second->GetEntityInfo();
	}

	return sceneInfo;
}