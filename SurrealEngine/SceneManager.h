#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>

#include "Manager.h"
#include <cstdint>

class Scene;
class Renderer;

class SceneManager : public Manager
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void Update();
	virtual void Draw();

	virtual void AddScene(Scene*);

	virtual Scene* GetScene(uint32_t);

	std::map<uint32_t, Scene*> scenes;

private:
	
	Scene* currentScene;
	bool initialized;

};

#endif // !RESOURCEMANAGER_H_
