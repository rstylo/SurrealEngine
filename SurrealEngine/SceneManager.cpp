#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Entity.h"
#include "Mesh.h"
#include "Resource.h"


SceneManager::SceneManager()
{
	Scene* startScene = new Scene();
	resourceManager = new ResourceManager();
	currentScene = startScene;



	//tempolarily, straks via commands en/of input in resource manager
	Entity* entity1 = new Entity(D3DXVECTOR3(0, 10, 0), D3DXVECTOR3(0, 0, 0));
	Entity* entity2 = new Entity(D3DXVECTOR3(0, 10, 5), D3DXVECTOR3(0, 2, 0));
	currentScene->AddEntity(entity1);
	currentScene->AddEntity(entity2);

	Resource* mesh = new Mesh();
	entity1->AddResource(mesh);						//drawt de resource
	entity2->AddResource(mesh);						//drawt de resource
	resourceManager->AddResource(mesh);				//bewaart de item voor hergebruik en clean up



	
}

void SceneManager::Init(LPDIRECT3DDEVICE9 device, InputHandler* _inputHandler, HWND* _hwnd, HWND* _hwnd2)
{
	currentScene->InitEntities(device);

	currentScene->AddCamera(0, D3DXVECTOR3(0, 5, -5), D3DXVECTOR3(0, 4, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-5, 15, 0), _hwnd, _inputHandler); //game camera
	currentScene->AddCamera(1, D3DXVECTOR3(0, 20, -10), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 70, 0), _hwnd2, _inputHandler); //dev camera

	currentScene->GetCamera(1)->SetLookAt(true);
	currentScene->GetCamera(1)->LookAt(D3DXVECTOR3(1, 2, 0));
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
		//currentScene->SetupMatrices(device);
		
		currentScene->SetupView(device, cam);
		currentScene->Draw(device);
		
		
	}
	
}

void SceneManager::SetupScene(LPDIRECT3DDEVICE9 device)
{
	if (currentScene != NULL)
	{
		currentScene->InitEntities(device);
		currentScene->SetupTerrain(device);
		currentScene->SetupLight(device);
	}
}

void SceneManager::doCommands()
{
	std::cout << std::endl;

	std::string line;
	std::getline(std::cin, line);


	int wordCount = -1;
	bool inWord = false;

	std::string param[10];
	std::cout << line << std::endl;
	for (int currentChar = 0; currentChar < line.size(); currentChar++)
	{
		if (line[currentChar] != ' ')
		{
			if (inWord == false)
			{
				wordCount++;
				inWord = true;
			}

			if(wordCount < 10)
				param[wordCount] += line[currentChar];
		}
		else
		{
			inWord = false;
		}

	}

	if (wordCount != -1 && param[0] == "create" && param[1] == "entity")
	{
		int extraParams[6];

		std::cout << "Position\n x:";
		std::cin >> extraParams[0];
		std::cout << "y:";
		std::cin >> extraParams[1];
		std::cout << "z:";
		std::cin >> extraParams[2];
		std::cout << "Rotation\n x:";
		std::cin >> extraParams[3];
		std::cout << "y:";
		std::cin >> extraParams[4];
		std::cout << "z:";
		std::cin >> extraParams[5];

		Entity* entity1 = new Entity(D3DXVECTOR3(extraParams[0], extraParams[1], extraParams[2]), D3DXVECTOR3(extraParams[3], extraParams[4], extraParams[5]));
		currentScene->AddEntity(entity1);

		Resource* mesh = new Mesh();
		entity1->AddResource(mesh);						//drawt de resource
		resourceManager->AddResource(mesh);				//bewaart de item voor hergebruik en clean up
	}

}