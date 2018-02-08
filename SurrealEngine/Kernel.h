/*! \file  Kernel.h
	\brief This class's main purpose is to initiate the 3d engine and control of the main routine
*/


#ifndef KERNEL_H_
#define KERNEL_H_

#include <iostream>
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

	bool Init(bool);				//! initialise in windowed mode or not
	bool Init(bool,int,int,int,int);//! initialise in windowed mode with 2 window sizes, will wait for input in console

	void Update();					//! main routine
	void Draw();					//! rendering routine

public:
	Wnd* gameDisplay;				//! window on which player view is displayed
	Wnd* devDisplay;				//! window on which the scene can be viewed in a different perspetive
private:

	bool initialized;
	Renderer* renderer;				
	SceneManager* sceneManager;		//!  pointer to a manager that controls the current scene

	InputHandler* inputHandler;		//!  pointer to inputhandler class, from which camera can get inputs
	bool expert;

	Console* console;				//! pointer to console class from which commands can be called

	Logger logger;


};
#endif // KERNEL_H_