#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>
#include <d3d9.h>
#include <dinput.h>


struct MouseValues {
	long x;
	long y;
	int dX;
	int dY;
	bool button0;
	bool button1;
};

class Mouse;
class Keyboard;
class Camera;

class InputHandler
{
public:
	InputHandler(HWND*);
	virtual ~InputHandler();
	void SaveReleaseDevice();
	virtual void Acquire();
	virtual bool Init();
	virtual void Update(Camera*);
	virtual void HandleKeys(Camera*);
	virtual void HandleMouse(Camera*);

private:
	Mouse* mouse;
	Keyboard* keyboard;
	byte* keybuffer;
	
	LPDIRECTINPUT dInput;

	MouseValues* mouseValues;
};

#endif
