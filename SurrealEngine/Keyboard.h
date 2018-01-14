/*
* Class: Keyboard.h
* Description : 
* Note : 
*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <d3d9.h>
#include <dinput.h>

class Keyboard
{
public:
	Keyboard(LPDIRECTINPUT);
	virtual ~Keyboard();
	bool Init();

	virtual void SaveReleaseDevice();
	virtual bool UpdateKeyBuffer();
	virtual bool CheckKeyPressed(byte);
	virtual bool SetWindow(HWND* _hwnd);
	virtual bool DoAcquire();

private:
	LPDIRECTINPUT dInput;
	LPDIRECTINPUTDEVICE dDevice;
	byte keybuffer[256];
};

#endif