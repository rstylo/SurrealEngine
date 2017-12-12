#ifndef KERNEL_H_
#define KERNEL_H_

#include <iostream>
#include <d3dx9.h>
#include <string>
#include <sstream>

class Renderer;
class Wnd;
class SceneManager;
class ResourceManager;

class Keyboard;

class Kernel													//deze klasse geliever niet abstract omdat hij van teveel andere klasse afhankelijk is
{
public:
	Kernel();														
	~Kernel();

    bool Init(bool);

	void Update();
	void Draw();

public:
	std::pair<Wnd*, Renderer*> gameDisplay;								
	std::pair<Wnd*, Renderer*> devDisplay;
private:

	bool initialized;

	SceneManager* sceneManager;
	ResourceManager* resourceManager;

	Keyboard* keyboard;


};
#endif // KERNEL_H_


