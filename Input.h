#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>
#include <iostream>
#include <sstream>

class Input
{
public:
	Input();
	virtual ~Input();
	
	virtual bool Init();

protected:
	RAWINPUTDEVICE rawInput[1];
};

#endif // !INPUT_H_
