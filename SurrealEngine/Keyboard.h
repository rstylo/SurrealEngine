/*! \file  Keyboard.h
	\brief an extention of inputhandler that hold and gets keyboard inputs
*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <d3d9.h>
#include <dinput.h>
#include "Logger.h"

class Keyboard
{
public:
	Keyboard(LPDIRECTINPUT);
	virtual ~Keyboard();
	bool Init();

	virtual void SaveReleaseDevice();
	virtual bool UpdateKeyBuffer();				//! update the inputbuffer
	virtual bool CheckKeyPressed(byte);			//! see if a key is on the keyboard is pressed
	virtual bool SetWindow(HWND* _hwnd);		//! set the window for coorperation
	virtual bool DoAcquire();

private:
	LPDIRECTINPUT dInput;						//! directx input from which keyboard is created
	LPDIRECTINPUTDEVICE dDevice;				//! directx input device
	byte keybuffer[256];						//! currently pressed keys
	Logger logger;
};

#endif