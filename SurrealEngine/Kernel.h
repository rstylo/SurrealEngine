#ifndef KERNEL_H_
#define KERNEL_H_

#include <d3dx9.h>
#include <string>
#include <list>
#include "GameEntity.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"

class Kernel
{
public:
	Kernel();														
	~Kernel();
    bool Init(HWND, bool);
	void Update();

private:
	Renderer* renderer;
	bool initialized;
	SceneManager* sceneManager;
	ResourceManager* resourceManager;
};
#endif // KERNEL_H_


