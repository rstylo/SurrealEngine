/*
* Class: SceneManager.h
* Description : This class manages scenes. loads and unloads them. And devicde which one is to be renderd
* Note :
*/


#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <windows.h>						
#include <d3dx9.h>
#include <cstdint>		//voor unique ids
#include <map>

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

	virtual void Init(LPDIRECT3DDEVICE9);
	virtual void Update();
	virtual void Draw(LPDIRECT3DDEVICE9, int);

	virtual Scene* CreateScene(std::string sceneName);
	virtual bool AddScene(Scene*);
	virtual Scene* GetScene(std::string);
	
	virtual void LoadScene(std::string);										//start loading process a given scene
	virtual void UnloadScene();													
	virtual bool IsLoading();

	virtual void SetupScene(LPDIRECT3DDEVICE9, InputHandler*, HWND*, HWND*);	//load the current scene's  objects into directx device


	 
	 //Command functions, will wait for input
	 void SpawnEntity();			
	 void CreateScene();	 
	 void SetScene();
	 void ChangeTerrain();
	 void MoveEntity();
	 void MoveTerrain();


	Scene* currentScene;

private:
	ResourceManager* resourceManager;
	std::map<std::string, Scene*> scenes;
	
	bool loading;
	bool initialized;
	

};

#endif // !SCENEMANAGER_H_
