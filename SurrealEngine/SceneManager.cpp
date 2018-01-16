#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Camera.h"

#include <iostream>
#include <fstream>

SceneManager::SceneManager()
{
	resourceManager = new ResourceManager();
	
	loading = false;
}

void SceneManager::Init(Renderer* device)
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

void SceneManager::Draw(Renderer* renderer, int cam)
{
	if (currentScene != NULL)
	{
		currentScene->SetupMatrices(renderer, cam);

		currentScene->Draw(renderer);
		currentScene->SetupView(renderer, cam);
	}
}

void SceneManager::SetupScene(Renderer* renderer, InputHandler* _inputHandler, HWND* _hwnd, HWND* _hwnd2)
{
	if (currentScene != NULL && loading == true)
	{
		currentScene->AddCamera(0, Vector3(-0.5, 0, 0), Vector3(-5, -15, 0), _hwnd, _inputHandler); //game camera
		currentScene->AddCamera(1, Vector3(1.5*pi, 0, 0), Vector3(0, -80, 0), _hwnd2, _inputHandler); //dev camera

		currentScene->InitEntities(renderer);

		currentScene->SetupSkybox(renderer);
		currentScene->SetupTerrain(renderer);
		currentScene->SetupLight(renderer);

		loading = false;
	}
}


void SceneManager::SpawnEntity()
{
	int extraParams[6];
	std::cout << "=Postion=\nx: ";
	std::cin  >> extraParams[0];
	std::cout << "y: ";
	std::cin >> extraParams[1];
	std::cout << "z: ";
	std::cin >> extraParams[2];
	std::cout << "=Rotation=\nx: ";
	std::cin >> extraParams[3];
	std::cout << "y: ";
	std::cin >> extraParams[4];
	std::cout << "z: ";
	std::cin >> extraParams[5];

	std::string meshName;
	std::cout << "MeshfileName:\n";
	std::cin >> meshName;

	currentScene->CreateEntityWithMesh(Vector3(extraParams[0], extraParams[1], extraParams[2]), Vector3(extraParams[3], extraParams[4], extraParams[5]), resourceManager->CreateMesh(meshName));


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

void SceneManager::MoveEntity()
{
	if (currentScene != NULL)
	{
		int extraParams[7];
		std::cout << "EntityId:\n: ";
		std::cin >> extraParams[6];
		if (!currentScene->GetEntity(extraParams[6]))
		{
			return;
		}

		std::cout << "=Postion-\nx: ";
		std::cin >> extraParams[0];
		std::cout << "y: ";
		std::cin >> extraParams[1];
		std::cout << "z: ";
		std::cin >> extraParams[2];
		std::cout << "-Rotation-\nx: ";
		std::cin >> extraParams[3];
		std::cout << "y: ";
		std::cin >> extraParams[4];
		std::cout << "z: ";
		std::cin >> extraParams[5];

		currentScene->MoveEntityTo(extraParams[6], Vector3(extraParams[0], extraParams[1], extraParams[2]), Vector3(extraParams[3], extraParams[4], extraParams[5]));
	}
}

void SceneManager::MoveTerrain()
{
	if (currentScene != NULL)
	{
		int extraParams[6];

		std::cout << "=Postion-\nx: ";
		std::cin >> extraParams[0];
		std::cout << "y: ";
		std::cin >> extraParams[1];
		std::cout << "z: ";
		std::cin >> extraParams[2];
		std::cout << "-Rotation-\nx: ";
		std::cin >> extraParams[3];
		std::cout << "y: ";
		std::cin >> extraParams[4];
		std::cout << "z: ";
		std::cin >> extraParams[5];

		currentScene->MoveTerrainTo(Vector3(extraParams[0], extraParams[1], extraParams[2]), Vector3(extraParams[3], extraParams[4], extraParams[5]));
	}
}


void SceneManager::LoadSceneFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line)) //read all lines
	{
		if (line == "scene")
		{
			std::string sceneName;
			std::getline(file, sceneName);

			this->CreateScene(sceneName);
			this->LoadScene(sceneName);
		}
		else if (line == "terrain")
		{
			std::string bitmap;
			std::getline(file, bitmap);
			std::string texture;
			std::getline(file, texture);

			currentScene->CreateTerrainWithTexture(bitmap, texture);
		}
		else if (line == "entity")
		{
			std::string meshName;
			std::getline(file, meshName);

			int extraParams[6];
			for (int i = 0; i < 6; i++)
			{
				file >> extraParams[i];
			}

			currentScene->CreateEntityWithMesh(
				Vector3(extraParams[0], extraParams[1], extraParams[2]),
				Vector3(extraParams[3], extraParams[4], extraParams[5]),
				resourceManager->CreateMesh(meshName)
			);
		}
	}
	file.close();
}

void SceneManager::SaveSceneToFile()
{
	std::ofstream saveFile;
	saveFile.open(currentScene->GetName());

	saveFile << currentScene->GetSceneInfo();

	saveFile.close();

}
