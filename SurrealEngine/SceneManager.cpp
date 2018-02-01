#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"



SceneManager::SceneManager()
{
	//! creates a resource manager
	resourceManager = new ResourceManager();
	
	loading = false;
}

void SceneManager::Init(Renderer* device)
{
	//! is empty
	renderer = device;
}

SceneManager::~SceneManager()
{
	//! deletes all scenes on destruction and releases and deletes all objects in the process
	for (std::map<std::string, Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++)
	{
		delete it->second;
	}

	scenes.clear();
}

Scene* SceneManager::CreateScene(std::string sceneName)
{
	//! returns created scene with given scene name if not existing
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
	//! add a scene if not already added
	if (scenes.find(_scene->GetName()) != scenes.end())
	{
		std::cout << "Scene: " << _scene->GetName() << " already exists!!" << std::endl;
		logger.Log("Failed to create Scene. " + _scene->GetName() + " already exists.", "Warning");
		return false;
	}
	scenes[_scene->GetName()] = _scene;
	return true;

}

Scene* SceneManager::GetScene(std::string _uuid)
{
	//! get a scene using its unique uid
	if (scenes.find(_uuid) != scenes.end())
		return scenes.find(_uuid)->second;

	return NULL;
}
void SceneManager::Update()
{
	//! calls update routin for current scene
	if (currentScene != NULL)
	{
		currentScene->Update();

	}
	else 
	{
		printf("no scene selected!");
		logger.Log("no scene selected!", "Warning");
	}
}

void SceneManager::LoadScene(std::string sceneName)
{
	//! loads scene with given name and sets it to current scene if existing. Unloads other scene to free space
	if (GetScene(sceneName) != NULL)
	{
		UnloadScene();
		currentScene = GetScene(sceneName);


		loading = true;
	}
	else
	{
		std::cout << "could not find scene: " << sceneName << std::endl;
		logger.Log("could not find scene: " + sceneName, "Warning");
	}


}

void SceneManager::UnloadScene()
{
	//! unloads current scene
	if(currentScene != NULL)
		currentScene->InvalidateObjects(renderer);

	currentScene = NULL;
}

bool SceneManager::IsLoading()
{
	//! returns if scene true when scene needs to be initialised
	return loading;
}

void SceneManager::Draw(Renderer* renderer, int cam)
{
	//! draws for given display
	if (currentScene != NULL)
	{
		currentScene->SetupMatrices(renderer, cam);

		currentScene->Draw(renderer);
		currentScene->SetupView(renderer, cam);
	}
}

void SceneManager::SetupScene(Renderer* renderer, InputHandler* _inputHandler, HWND* _hwnd, HWND* _hwnd2)
{
	//! setup scene with a inputhandler and two windows to display on
	if (currentScene != NULL && loading == true)
	{
		currentScene->AddCamera(0, Vector3(-0.5, 0, 0), Vector3(-5, -15, 0), _hwnd, _inputHandler); //game camera
		currentScene->AddCamera(1, Vector3(1.5*pi, 0, 0), Vector3(-50, -80, -50), _hwnd2, _inputHandler); //dev camera

		currentScene->InitEntities(renderer);

		currentScene->SetupSkybox(renderer);
		currentScene->SetupTerrain(renderer);
		currentScene->SetupLight(renderer);

		currentScene->SetCameraHeightMap();

		loading = false;
	}
}

void SceneManager::SpawnEntityMesh()
{
	float extraParams[6];
	std::cout << "=Postion=\nx: ";
	std::cin >> extraParams[0];
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

	currentScene->CreateEntityWithResource(Vector3(extraParams[0], extraParams[1], extraParams[2]), Vector3(extraParams[3], extraParams[4], extraParams[5]), resourceManager->CreateMesh(meshName));
}

void SceneManager::SpawnEntityObject()
{
	float extraParams[6];
	std::cout << "=Postion=\nx: ";
	std::cin >> extraParams[0];
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

	std::string objectName;
	std::cout << "name the object:\n";
	std::cin >> objectName;

	currentScene->CreateEntityWithResource(Vector3(extraParams[0], extraParams[1], extraParams[2]), Vector3(extraParams[3], extraParams[4], extraParams[5]), resourceManager->CreateObj(objectName));


}

void SceneManager::SaveScene()
{
	if (currentScene != NULL)
	{
		std::string fileName;
		std::cout << "enter file name: ";
		std::cin >> fileName;
		SaveSceneToFile(fileName);
	}
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

	//set default values
	Scene* newScene = GetScene(sceneName);
	newScene->CreateTerrainWithTexture("map.bmp", "texture1.jpg");
	newScene->CreateSkyboxWithTexture("skybox.jpg");
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
		loading = true;
	}
}

void SceneManager::MoveEntity()
{
	if (currentScene != NULL)
	{
		float extraParams[6];
		int entityId;
		std::cout << "EntityId:\n: ";
		std::cin >> entityId;
		if (!currentScene->GetEntity(entityId))
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

		currentScene->MoveEntityTo(entityId, Vector3(extraParams[0], extraParams[1], extraParams[2]), Vector3(extraParams[3], extraParams[4], extraParams[5]));
		std::cout << "Entity " << entityId << " moved" << std::endl;
	}
}

void SceneManager::MoveTerrain()
{
	if (currentScene != NULL)
	{
		float extraParams[6];

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
	if (file.fail()) {
		file.open(("..\\" + fileName));
		if (file.fail()) {
			logger.Log("File " + fileName + " not found", "Error");
			std::cout << "File " + fileName + " not found" << std::endl;
			return;
		}
	}
	std::string line;
	while (std::getline(file, line)) //read all lines
	{
		if (line == "scene")
		{
			std::string sceneName;
			std::getline(file, sceneName);

			CreateScene(sceneName);
			LoadScene(sceneName);
		}
		else if (line == "terrain")
		{
			std::string bitmap;
			std::getline(file, bitmap);
			std::string terrainTexture;
			std::getline(file, terrainTexture);

			currentScene->CreateTerrainWithTexture(bitmap, terrainTexture);
		}
		else if (line == "skybox")
		{
			std::string skyboxTexture;
			std::getline(file, skyboxTexture);

			currentScene->CreateSkyboxWithTexture(skyboxTexture);
		}
		else if (line == "entity")
		{
			std::string meshName;
			std::getline(file, meshName);

			float extraParams[6];
			for (int i = 0; i < 6; i++)
			{
				file >> extraParams[i];
			}

			currentScene->CreateEntityWithResource(
				Vector3(extraParams[0], extraParams[1], extraParams[2]),
				Vector3(extraParams[3], extraParams[4], extraParams[5]),
				resourceManager->CreateMesh(meshName)
			);
		}
	}
	file.close();

}

void SceneManager::SaveSceneToFile(std::string fileName)
{
	std::ofstream saveFile;
	saveFile.open(fileName + ".txt");

	saveFile << currentScene->GetSceneInfo();
	
	saveFile.close();
	std::cout << "Saved scene to file " << fileName << ".txt" << std::endl;
	logger.Log("Saved scene to file " + fileName+".txt", "Info");
}

void SceneManager::CreateLevel() {
	std::string sceneName, terrainMap, terrainTexture, skyboxImg;
	std::cout << "Enter the name of the scene you want to create: ";
	std::cin >> sceneName;
	CreateScene(sceneName);
	LoadScene(sceneName);
	ChangeTerrain();
	std::cout << "Skybox image: ";
	std::cin >> skyboxImg;
	currentScene->CreateSkyboxWithTexture(skyboxImg);
	logger.Log("Created scene " + sceneName, "Info");
}
