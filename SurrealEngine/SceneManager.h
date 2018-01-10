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

	virtual void Init(LPDIRECT3DDEVICE9, InputHandler*, HWND*, HWND*);
	virtual void Update();
	virtual void Draw(LPDIRECT3DDEVICE9, int);

	virtual void AddScene(Scene*);
	virtual Scene* GetScene(std::string);

	virtual void SetupScene(LPDIRECT3DDEVICE9);

	virtual void SpawnEntity();


	Scene* currentScene;

private:
	ResourceManager* resourceManager;
	std::map<std::string, Scene*> scenes;
	
	
	bool initialized;

};

#endif // !SCENEMANAGER_H_
