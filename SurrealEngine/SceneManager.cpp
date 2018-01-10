#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Entity.h"
#include "Mesh.h"
#include "Resource.h"
#include "Terrain.h"


SceneManager::SceneManager()
{
	Scene* startScene = new Scene("Scene0");
	resourceManager = new ResourceManager();

	currentScene = startScene;


}

void SceneManager::Init(LPDIRECT3DDEVICE9 device, InputHandler* _inputHandler, HWND* _hwnd, HWND* _hwnd2)
{
	currentScene->InitEntities(device);

	currentScene->AddCamera(0, D3DXVECTOR3(0, 5, -5), D3DXVECTOR3(0, 4, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-5, -50, 0), _hwnd, _inputHandler); //game camera
	currentScene->AddCamera(1, D3DXVECTOR3(0, 20, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, -100, 0), _hwnd2, _inputHandler); //dev camera

	currentScene->GetCamera(1)->SetLookAt(true);
	currentScene->GetCamera(1)->LookAt(D3DXVECTOR3(0, 0, 0));
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
	if (scenes.find(_scene->GetName()) != scenes.end())
		return;
	scenes[_scene->GetName()] = _scene;
	currentScene = _scene;

}

Scene* SceneManager::GetScene(std::string _uuid)
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
		currentScene->SetupMatrices(device);

		currentScene->SetupView(device, cam);
		currentScene->Draw(device);


	}

}

void SceneManager::SetupScene(LPDIRECT3DDEVICE9 device)
{
	if (currentScene != NULL)
	{
		currentScene->InitEntities(device);
		currentScene->SetupTerrain(device, "map1.bmp", "texture3.jpg", "skybox.jpg");
		currentScene->SetupLight(device);
	}
}


void SceneManager::SpawnEntity()
{
	int extraParams[10];
	std::cout << "Postion:\nx: ";
	std::cin  >> extraParams[0];
	std::cout << "x: ";
	std::cin >> extraParams[1];
	std::cout << "y: ";
	std::cin >> extraParams[2];
	std::cout << "z: ";
	std::cin >> extraParams[3];
	std::cout << "Rotation:\nx: ";
	std::cin >> extraParams[0];
	std::cout << "x: ";
	std::cin >> extraParams[1];
	std::cout << "y: ";
	std::cin >> extraParams[2];
	std::cout << "z: ";
	std::cin >> extraParams[3];

	std::string meshName;
	std::cout << "TextureName:\n";
	std::cin >> meshName;

	currentScene->CreateEntityWithMesh(D3DXVECTOR3(extraParams[0], extraParams[1], extraParams[2]), D3DXVECTOR3(extraParams[3], extraParams[4], extraParams[5]), resourceManager->CreateMesh(meshName));


}