#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>
#include <d3d9.h>
#include <dinput.h>

class Mouse;
class Keyboard;
class Camera;

class InputHandler
{
public:
	InputHandler(HWND*);
	virtual ~InputHandler();
	virtual void Acquire();
//	virtual bool GetKey(byte);
	virtual bool Init();
	virtual void Update(Camera*);

private:
	Mouse* mouse;
	Keyboard* keyboard;
	
	LPDIRECTINPUT dInput;

	std::string currentKey;
	std::string lastKey;


};

#endif
