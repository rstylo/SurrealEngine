#ifndef KERNEL_H_
#define KERNEL_H_

#include <d3dx9.h>
#include <string>
#include <list>
#include "GameEntity.h"
#include "Scene.h"
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
	Renderer* renderer;
	bool initialized;
	Scene* myScene;
};
#endif // KERNEL_H_


