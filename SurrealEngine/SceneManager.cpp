#include "SceneManager.h"
#include "Scene.h"


SceneManager::SceneManager()
	:Manager("SceneManager")			//zie manager of entitymanager
{
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
	if (scenes.find(_scene->GetId()) != scenes.end()) return;
	scenes[_scene->GetId()] = _scene;

}

Scene* SceneManager::GetScene(uint32_t _uuid)
{
	if (scenes.find(_uuid) != scenes.end())
		return scenes.find(_uuid)->second;

	return NULL;
}
void SceneManager::Update()
{
}

void SceneManager::Draw()
{
	//doet niks
}