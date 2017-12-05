#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>
#include <d3dx9.h>
#include "Manager.h"
#include <cstdint>
#include "GameEntity.h"

class Entity;

class EntityManager : public Manager
{
public:
	EntityManager();
	virtual ~EntityManager();
	void Init(LPDIRECT3DDEVICE9);
	void DrawEntities();
	virtual Entity* GetEntity(uint32_t);

private:
	std::map<uint32_t, Entity*> entities;
	//test gameobject
	GameEntity* game;
};

#endif // !ENTITYMANAGER_H_
