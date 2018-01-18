
/*! \file  Scene.h
	\brief This class manages scenes. loads and unloads them. And decides which one is to be renderd
*/


#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <windows.h>						
//#include <d3dx9.h>
#include <cstdint>		//voor unique ids
#include <map>
#include "DirectXRenderer.h"

#include <iostream>
#include <string>

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
	virtual void Draw(Renderer*, int);

	virtual Scene* CreateScene(std::string sceneName);
	virtual bool AddScene(Scene*);
	virtual Scene* GetScene(std::string);
	
	virtual void LoadScene(std::string);										//! start loading process for a given scene
	virtual void UnloadScene();													//! free scene space
	virtual bool IsLoading();													

	virtual void SetupScene(Renderer*, InputHandler*, HWND*, HWND*);			//! load the current scene's  objects into directx device

	virtual void LoadSceneFromFile(std::string);
	virtual void SaveSceneToFile(std::string);

		
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
	

};

#endif // !SCENEMANAGER_H_
