#ifndef SCENE_H_
#define SCENE_H_


#include <d3dx9.h>
#include <cstdint>							//voor uint32_t'
#include <Windows.h>
//#include <string>
#include <map>

class Terrain;
class Camera;
class Entity;
class InputHandler;
class Skybox;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual uint32_t GetId();

	virtual bool InitEntities(LPDIRECT3DDEVICE9);
	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual void Update();

	virtual void SetupView(LPDIRECT3DDEVICE9, int);
	virtual void SetupMatrices(LPDIRECT3DDEVICE9);
	virtual void SetupTerrain(LPDIRECT3DDEVICE9);
	virtual void SetupLight(LPDIRECT3DDEVICE9);

	virtual void AddCamera(int, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, HWND*, InputHandler*);
	virtual Camera* GetCamera(int cam);

	virtual void AddEntity(Entity*);
	virtual Entity* GetEntity(uint32_t);
	
private:
	uint32_t id;

	virtual std::string CurrentDirectory(std::string);

private:
	Terrain* terrain;
	Skybox* skybox;

	std::map<int, Camera*> cameras;
	std::map<uint32_t, Entity*> entities;


};

#endif // SCENE_H_