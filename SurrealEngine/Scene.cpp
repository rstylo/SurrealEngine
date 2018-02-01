#include "Scene.h"
#include "Terrain.h"
#include "Camera.h"
#include "Entity.h"
#include "Skybox.h"
#include "Renderer.h"

Scene::Scene(std::string _name)
	:name(_name)
{
	//! yialiazes with scene name, unique id, skybox, terrain and origin transform
	id = reinterpret_cast<uint32_t>(this);

	skybox = new Skybox();
	skybox->SetTexture("texture1.jpg");

	terrain = new Terrain();

	originTransform.SetPosition(Vector3(0, 0, 0));
	originTransform.SetRotation(Vector3(0, 0, 0));
		
}


Scene::~Scene()
{

	//! deletes all objects in scene
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
	//! calls init function in entity
	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Init(renderer);
	}

	return true;
}


void Scene::InvalidateObjects(Renderer* renderer)
{
	//! releases all drawable objects to free space
	if (skybox != NULL)
		skybox->Invalidate(renderer);
	if (terrain != NULL)
		terrain->Invalidate(renderer);

}

void Scene::SetupSkybox(Renderer* renderer)
{
	//! initialises skybox if present
	if (skybox != NULL)
	{
		if (skybox->Init(renderer))
			skybox->Create();
	}
}

void Scene::SetupTerrain(Renderer* renderer)
{
	//! initialises terrain if present
	if (terrain != NULL)
	{

		terrain->Init(renderer);
	}

}

void Scene::SetupMatrices(Renderer* renderer, int cam)
{
	//! setups scene's for a specific view world matrices 
	originTransform.SetupMatrices(renderer);
	if (!(cameras.empty())) {
		if (cameras[cam] != NULL) {
			originTransform.SetPosition(cameras[cam]->GetPosition());
			originTransform.SetRotation(cameras[cam]->GetRotation());
		}
	}
}

void Scene::SetCameraHeightMap()
{
	//! sets the height of the camera to terrain height if the terrain is available
	if (!(cameras.empty() && terrain != NULL)) {
		if (cameras[0] != NULL)
			if (terrain->getInitialized())
				cameras[0]->SetHeight(terrain->getHeightArray(), terrain->getTerrainDepth(), terrain->getTerrainWidth());
	}
}

void Scene::SetupView(Renderer* renderer, int cam)
{

	//! setups camera's view matrix
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
	//! initialises ambient lighting, will only work for normalised vertices
	if (renderer != NULL)
		renderer->SetupLight();
}

void Scene::Draw(Renderer* renderer)
{
	//! drawing routine, draws skybox, terrain and all entities and their resources if possible
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
	//! add a camera with a identification number with a rotation and position vector. 
	if (cameras.find(cam) == cameras.end())
		cameras[cam] = new Camera(_rotation, _position, _hwnd, _inputHandler);
	else
		printf("camera %d already exists!! \n", cam);
		//logger.Log("Tried to add camera " + std::to_string(cam) + " but it already exists", "Warning");
}


Camera* Scene::GetCamera(int cam)
{
	//! returns corresponding camera, 0 = game window
	if (cameras.find(cam) != cameras.end())
		return cameras.find(cam)->second;

	return NULL;
}

void Scene::AddEntity(Entity* _entity)
{
	//! add an entity for managing purpose
	if (entities.find(_entity->GetId()) != entities.end()) {				
		printf("entity %d already exists!! \n", _entity->GetId());
		return;
	}

	entities[_entity->GetId()] = _entity;									
	printf("added entity %d... \n", _entity->GetId());
}

Entity* Scene::GetEntity(uint32_t _uuid)
{
	//! returns pointer to entity
	if (entities.find(_uuid) != entities.end())
		return entities.find(_uuid)->second;

	std::cout << " could not find entity " << _uuid << std::endl;
	return NULL;
}

void Scene::RemoveEntity(uint32_t _uuid)
{
	//! removes specified entity, if existing in this scene
	if (entities.find(_uuid) != entities.end())
		delete entities.find(_uuid)->second;
	else
		std::cout << " could not find entity "<< _uuid << std::endl;
}

void Scene::MoveTerrainTo(Vector3 position, Vector3 rotation)
{
	//! move the terrain with a position and rotation vector
	terrain->transform.SetPosition(position);
	terrain->transform.SetRotation(rotation);
}

void Scene::MoveEntityTo(uint32_t _uuid, Vector3 position, Vector3 rotation)
{
	//! changes specified entities transform to a position and rotation
	GetEntity(_uuid)->transform.SetPosition(position);
	GetEntity(_uuid)->transform.SetRotation(rotation);
}

void Scene::Update()
{
	//! update routine for the scene, updates camera
	if (!cameras.empty()) {
		if (cameras[0] != NULL)
			cameras[0]->Update();
		if (cameras[1] != NULL)
			cameras[1]->Update();
	}
}

std::string Scene::CurrentDirectory(std::string str)
{
	//! return path to currentdirectory + a name
	char dir[MAX_PATH + 1];
	GetCurrentDirectoryA(sizeof(dir), dir); // **** win32 specific ****
	return dir + str;
}

std::string Scene::GetName()
{
	//! get identification scene's name
	return name;
}

void Scene::CreateEntityWithResource(Vector3 _position, Vector3 _rotation, Resource* mesh)
{
	//! creates an entity with a resource
	Entity* entity1 = new Entity(_position, _rotation);
	AddEntity(entity1);

	entity1->AddResource(mesh);
}

bool Scene::CreateTerrainWithTexture(std::string map, std::string texture)
{
	//! creates/changes terrain with a given heightmap and texture
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

bool Scene::CreateSkyboxWithTexture(std::string texture)
{
	//! creates/changes skybox with a given texture
	if (skybox == NULL)
	{
		skybox = new Skybox();
		skybox->SetTexture(texture);
		return true;
	}
	else
	{
		skybox->SetTexture(texture);
		printf("skybox already exists in scene, texture has been changed!! \n");
		return false;
	}
}

std::string Scene::GetSceneInfo()
{
	//! get information of the scene to save to a file
	std::string sceneInfo;
	sceneInfo += "scene\n";
	sceneInfo += GetName();
	sceneInfo += "\n";

	sceneInfo += "terrain\n";
	sceneInfo += terrain->GetMapFileName();
	sceneInfo += "\n";
	sceneInfo += terrain->GetTextureName();
	sceneInfo += "\n";
	sceneInfo += "skybox\n";
	sceneInfo += skybox->GetTexture();
	sceneInfo += "\n";

	for (auto it = entities.begin(); it != entities.end(); it++)		
	{
		sceneInfo += it->second->GetEntityInfo();
	}

	return sceneInfo;
}