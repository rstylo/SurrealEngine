#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>

#include <d3dx9.h>
#include <cstdint>

class InputHandler;
class Scene;
class Renderer;
class Entity;

class SceneManager
{
public:
	SceneManager(InputHandler*);
	virtual ~SceneManager();

	virtual void Update();
	virtual void Draw(LPDIRECT3DDEVICE9, int);

	virtual void AddScene(Scene*);

	virtual Scene* GetScene(uint32_t);

	std::map<uint32_t, Scene*> scenes;

	virtual void SetupScene(LPDIRECT3DDEVICE9);

	virtual void AddEntity(Entity*);
	virtual Entity* GetEntity(uint32_t);

	virtual Scene* GetCurrentScene();



private:
	
	Scene* currentScene;
	std::map<uint32_t, Entity*> entities;
	bool initialized;

};

#endif // !RESOURCEMANAGER_H_
