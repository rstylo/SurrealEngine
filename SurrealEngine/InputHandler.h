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
	virtual void AddDevice(HWND*);
	virtual void SaveReleaseDevice();
	virtual bool Init();
	virtual void Update(Camera*,int);
	virtual void HandleKeys(Camera*,int);
	virtual void HandleMouse(Camera*,int);
	virtual bool SetWnd(int);

private:
	Mouse* mouse[5];
	Keyboard* keyboard[5];
	Camera* camera[5];
	HWND* wnd[5];
	int amount;
	int window;

	HWND* currentWindow;

	byte* keybuffer[5];
	
	LPDIRECTINPUT dInput;

	MouseValues* mouseValues[5];
};

#endif
