#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"


SceneManager::SceneManager()
{
	resourceManager = new ResourceManager();
	
	loading = false;
}

void SceneManager::Init(LPDIRECT3DDEVICE9 device)
{
	
}

SceneManager::~SceneManager()
{
	for (auto it = scenes.begin(); it != scenes.end(); it++)
	{
		delete it->second;
	}

	scenes.clear();
}

Scene* SceneManager::CreateScene(std::string sceneName)
{
	Scene* scene = new Scene(sceneName);
	if (AddScene(scene))
	{
		return scene;
	}

	delete scene;
	return NULL;
}

bool SceneManager::AddScene(Scene* _scene)
{
	if (scenes.find(_scene->GetName()) != scenes.end())
	{
		std::cout << "Scene: " << _scene->GetName() << " already exists!!" << std::endl;
		return false;
	}
	scenes[_scene->GetName()] = _scene;
	return true;

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
	else 
	{
		printf("no scene selected!");
	}
}

void SceneManager::LoadScene(std::string sceneName)
{
	if (GetScene(sceneName) != NULL)
	{
		UnloadScene();
		currentScene = GetScene(sceneName);


		loading = true;
	}
	else
	{
		std::cout << "could not find scene: " << sceneName << std::endl;
	}


}

void SceneManager::UnloadScene()
{
	if(currentScene != NULL)
		currentScene->InvalidateObjects();

	currentScene = NULL;
}

bool SceneManager::IsLoading()
{
	return loading;
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

void SceneManager::SetupScene(LPDIRECT3DDEVICE9 device, InputHandler* _inputHandler, HWND* _hwnd, HWND* _hwnd2)
{
	if (currentScene != NULL && loading == true)
	{
		currentScene->AddCamera(0, D3DXVECTOR3(0, 5, -5), D3DXVECTOR3(0, 4, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-5, -50, 0), _hwnd, _inputHandler); //game camera
		currentScene->AddCamera(1, D3DXVECTOR3(0, 20, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, -100, 0), _hwnd2, _inputHandler); //dev camera

		currentScene->CreateTerrainWithTexture("map.bmp", "texture3.jpg");

		currentScene->InitEntities(device);

		currentScene->SetupSkybox(device);
		currentScene->SetupTerrain(device);
		currentScene->SetupLight(device);

		loading = false;
	}


}


void SceneManager::SpawnEntity()
{
	int extraParams[10];
	std::cout << "Postion:\nx: ";
	std::cin  >> extraParams[0];
	std::cout << "y: ";
	std::cin >> extraParams[1];
	std::cout << "z: ";
	std::cin >> extraParams[2];
	std::cout << "Rotation:\nx: ";
	std::cin >> extraParams[3];
	std::cout << "y: ";
	std::cin >> extraParams[4];
	std::cout << "z: ";
	std::cin >> extraParams[5];

	std::string meshName;
	std::cout << "MeshfileName:\n";
	std::cin >> meshName;

	currentScene->CreateEntityWithMesh(D3DXVECTOR3(extraParams[0], extraParams[1], extraParams[2]), D3DXVECTOR3(extraParams[3], extraParams[4], extraParams[5]), resourceManager->CreateMesh(meshName));


}

void SceneManager::SetScene()
{
	std::string sceneName;
	std::cout << "SceneName:\n";
	std::cin >> sceneName;
	LoadScene(sceneName);
}
void SceneManager::CreateScene()
{
	std::string sceneName;
	std::cout << "SceneName:\n";
	std::cin >> sceneName;
	CreateScene(sceneName);
}

void SceneManager::ChangeTerrain()
{
	if (currentScene != NULL)
	{
		std::string hMapName;
		std::cout << "HeightMapFileName:\n";
		std::cin >> hMapName;

		std::string textureName;
		std::cout << "TextureFileName:\n";
		std::cin >> textureName;
		currentScene->CreateTerrainWithTexture(hMapName, textureName);
	}
}