#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>

#include "Manager.h"
#include <cstdint>

class Entity;

class EntityManager : public Manager
{
public:
	EntityManager();
	virtual ~EntityManager();
	virtual void Update();
	virtual void Draw();

	virtual void AddEntity(Entity*);
	virtual Entity* GetEntity(uint32_t);

private:
	std::map<uint32_t, Entity*> entities;


};

#endif // !ENTITYMANAGER_H_
