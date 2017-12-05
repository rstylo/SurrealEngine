#ifndef KERNEL_H_
#define KERNEL_H_

#include <d3dx9.h>
#include <string>
#include <list>
#include "GameEntity.h"
#include "Manager.h"
#include "EntityManager.h"
#include "Renderer.h"

class Kernel
{
public:
	Kernel();														
	~Kernel();
    bool Init(HWND, bool);
	void Update();
	void Draw();

private:
	Manager* GetManager(std::string);
	std::list<Manager*> managers;
	Renderer* renderer;
	bool initialized;
	EntityManager* myEntityManager;
};
#endif // KERNEL_H_


