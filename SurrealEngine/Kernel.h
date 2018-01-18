/*
* Class: Kernel.h
* Description : 
* Note : 
*/


#ifndef KERNEL_H_
#define KERNEL_H_

#include <iostream>
#include <d3dx9.h>
#include <string>
#include <sstream>
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"

class Renderer;
class Wnd;
class SceneManager;
class ResourceManager;
class InputHandler;
class Console;

class Kernel													
{
public:
	Kernel();
	~Kernel();

	bool Init(bool);
	bool Init(bool,int,int,int,int);

	void Update();
	void Draw();

public:
	Wnd* gameDisplay;
	Wnd* devDisplay;
private:

	bool initialized;
	Renderer* renderer;
	SceneManager* sceneManager;
	//LPDIRECT3DDEVICE9* device;
	bool expert;

	InputHandler* inputHandler;
	Console* console;




};
#endif // KERNEL_H_