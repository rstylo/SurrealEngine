#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <windows.h>						
#include <d3dx9.h>
#include <cstdint>		//voor unique ids
#include <map>

class Scene;
class Renderer;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void Update();
	virtual void Draw(LPDIRECT3DDEVICE9, int);

	virtual void AddScene(Scene*);
	virtual Scene* GetScene(uint32_t);
	virtual void SetupScene(LPDIRECT3DDEVICE9);





private:
	std::map<uint32_t, Scene*> scenes;
	Scene* currentScene;
	bool initialized;

};

#endif // !SCENEMANAGER_H_
