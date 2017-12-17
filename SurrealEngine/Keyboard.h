#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <d3d9.h>
#include <dinput.h>

class Keyboard
{
public:
	Keyboard(HWND*, LPDIRECTINPUT);
	virtual ~Keyboard();
	bool Init();

	virtual void SaveReleaseDevice();
	bool CheckKeyPressed();
	virtual byte * GetKeyBuffer();
	virtual bool DoAcquire();

private:
	HWND* wnd;
	LPDIRECTINPUT dInput;
	LPDIRECTINPUTDEVICE dDevice;
	byte keybuffer[256];
};

#endif