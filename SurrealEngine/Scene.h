#ifndef SCENE_H_
#define SCENE_H_


#include <d3dx9.h>
#include <cstdint>							//voor uint32_t'
#include <Windows.h>
#include <map>

class Terrain;
class Camera;
class Entity;
class InputHandler;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual uint32_t GetId();

	virtual void SetupMatrices(LPDIRECT3DDEVICE9, int);
	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual void Update();

	virtual void SetupTerrain(LPDIRECT3DDEVICE9);
	

	virtual void AddEntity(Entity*);
	virtual Entity* GetEntity(uint32_t);

	virtual void AddCamera(int, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, InputHandler*);
	
private:
	uint32_t id;

private:
	Terrain* terrain;

	std::map<int, Camera*> cameras;
	std::map<uint32_t, Entity*> entities;


};

#endif // SCENE_H_