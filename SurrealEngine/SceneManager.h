/*! \file  SceneManager.h
	\brief This class manages scenes. loads and unloads them. And decides which one is to be renderd
*/


#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <cstdint>		//voor unique ids
#include <map>
#include "Renderer.h"

#include <iostream>
#include <fstream>

#include <string>
#include "logger.h"

class InputHandler;
class Scene;
class Renderer;
class ResourceManager;
class Terrain;


class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void Init(Renderer*);
	virtual void Update();
	virtual void Draw(Renderer*, int);											//! draw objects of display (int) into given rendering device

	virtual Scene* CreateScene(std::string sceneName);							//! create a scene if no other scene with the same name exists else it returns NULL ptr
	virtual bool AddScene(Scene*);												//! add a given scene, returns true if no other similar scene exists
	virtual Scene* GetScene(std::string);										//! get a scene with given name
	
	virtual void LoadScene(std::string);										//! start loading process for a given scene
	virtual void UnloadScene();													//! free scene space
	virtual bool IsLoading();													

	virtual void SetupScene(Renderer*, InputHandler*, HWND*, HWND*);			//! load the current scene's  objects into directx device and creeates cameras

	virtual void LoadSceneFromFile(std::string);								//! load scene from a text file and unloads old scene while at it
	virtual void SaveSceneToFile(std::string);									//! save current scene to a text file
	virtual void CreateLevel();
		
	 void SpawnEntityMesh();													//! Command function, will wait for input from console
	 void SpawnEntityObject();													//! Command function, will wait for input from console
	 void CreateScene();														//! Command function, will wait for input from console
	 void SetScene();															//! Command function, will wait for input from console
	 void SaveScene();															//! Command function, will wait for input from console
	 void ChangeTerrain();														//! Command function, will wait for input from console
	 void MoveEntity();															//! Command function, will wait for input from console
	 void MoveTerrain();														//! Command function, will wait for input from console

	Scene* currentScene;

private:
	ResourceManager* resourceManager;											//! pointer to resourceManager that holds all active and not active resources
	std::map<std::string, Scene*> scenes;										//! all scenes with their identification name

	bool loading;
	bool initialized;
	
	Logger logger;

	Renderer* renderer;

};

#endif // !SCENEMANAGER_H_
