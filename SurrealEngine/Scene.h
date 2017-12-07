#ifndef Scene_H_
#define Scene_H_

#include <windows.h>						//voor unique ids
#include <map>
#include <d3dx9.h>
#include <cstdint>
#include "GameEntity.h"
#include "Entity.h"
#include "Terrain.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	void Init(LPDIRECT3DDEVICE9);
	void DrawEntities();
	virtual Entity* GetEntity(uint32_t);

private:
	std::map<uint32_t, Entity*> entities;
	//test gameobject
	GameEntity* game;
	Terrain* terrain;

};

#endif // !Scene_H_
