#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <d3d9.h>
#include <dinput.h>

class Keyboard
{
public:
	Keyboard::Keyboard(HWND*, LPDIRECTINPUT);
	virtual ~Keyboard();
	bool Init();

	virtual void SaveReleaseDevice();

	char CheckKeyPressed();
	
	virtual bool DoAcquire();

private:
	HWND* wnd;
	LPDIRECTINPUT dInput;
	LPDIRECTINPUTDEVICE dDevice;
	char keybuffer[256];
};

#endif