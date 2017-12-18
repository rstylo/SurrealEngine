#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"


SceneManager::SceneManager(InputHandler* _inputHandler)
{
	Scene* startScene = new Scene();
	currentScene = startScene;
	
	startScene->AddCamera(0, D3DXVECTOR3(0, 5, -5), D3DXVECTOR3(0, 4, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-5, -50, 0), _inputHandler); //game camera
	startScene->AddCamera(1, D3DXVECTOR3(0, 20, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, -100, 0), _inputHandler); //dev camera

	//startScene->AddEntity(new Entity(1, 5, 1));
}


SceneManager::~SceneManager()
{
	for (auto it = scenes.begin(); it != scenes.end(); it++)
	{
		delete it->second;
	}

	scenes.clear();
}

void SceneManager::AddScene(Scene* _scene)
{
	if (scenes.find(_scene->GetId()) != scenes.end()) 
		return;
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
	if (currentScene != NULL)
	{

		currentScene->Update();

	}
}

void SceneManager::Draw(LPDIRECT3DDEVICE9 device, int cam)
{
	if (currentScene != NULL)
	{
		currentScene->SetupMatrices(device, cam);
		currentScene->Draw(device);
	}
	
}

void SceneManager::SetupScene(LPDIRECT3DDEVICE9 device)
{
	if (currentScene != NULL)
	{
		
		currentScene->SetupTerrain(device);
		
	}
}

