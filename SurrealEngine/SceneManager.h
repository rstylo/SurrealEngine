#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <list>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	Scene* GetCurrentScene();

private:
	Scene* currentScene;
	std::list<Scene*> Scenes;
};

#endif // !SCENEMANAGER_H_
