#include "SceneManager.h"

SceneManager::SceneManager()
{
	//make an default scene
	currentScene = new Scene();
	//add scene to list
	Scenes.push_front(currentScene);
}

SceneManager::~SceneManager()
{

}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

