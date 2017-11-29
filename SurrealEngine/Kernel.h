#ifndef KERNEL_H_
#define KERNEL_H_

#include <d3dx9.h>
#include <string>
#include <list>

class Sprite;
class Renderer;
class Manager;
class Entity;

class Kernel													//deze klasse geliever niet abstract omdat hij van teveel andere klasse afhankelijk is
{
public:
	Kernel();														
	~Kernel();

    bool Init(HWND, bool);

	void Update();
	void Draw();

	bool CreateEntity(std::string, int, int, float, float, float); //mishien wel handig parameter namen ook hierbij //temp functie

private:
	Manager* GetManager(std::string);

private:
	std::list<Manager*> managers;
	Renderer* renderer;

	bool initialized;


};
#endif // KERNEL_H_


