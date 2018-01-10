#ifndef KERNEL_H_
#define KERNEL_H_

#include <iostream>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include "DirectXRenderer.h"

class Renderer;
class Wnd;
class SceneManager;
class ResourceManager;
class InputHandler;
class Console;

class Kernel													//deze klasse geliever niet abstract omdat hij van teveel andere klasse afhankelijk is
{
public:
	Kernel();
	~Kernel();

	bool Init(bool);

	void Update();
	void Draw();

public:
	Wnd* gameDisplay;
	Wnd* devDisplay;
private:

	bool initialized;
	Renderer* renderer;
	SceneManager* sceneManager;
	LPDIRECT3DDEVICE9* device;

	InputHandler* inputHandler;
	Console* console;




};
#endif // KERNEL_H_