/*! \file  Keyboard.h
	\brief an extention of inputhandler that hold and gets keyboard inputs
*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <dinput.h>
#include "Logger.h"

class Keyboard
{
public:
	Keyboard();
	virtual ~Keyboard();
	virtual bool Init(LPDIRECTINPUT, HWND*);	//! Creates a keyboard inputdevice and links it with the window

	virtual void SaveReleaseDevice();
	virtual bool UpdateKeyBuffer();				//!	Updates the values read from the keyboard into the keybuffer
	virtual bool CheckKeyPressed(byte);			//! Checks in the key buffer if the given key is pressed or not
	virtual bool SetWindow(HWND* _hwnd);		//!	Links the keyboard inputdevice with a different window
	virtual bool DoAcquire();					//!	Checks if there is a keyboard connected

private:
	LPDIRECTINPUTDEVICE dDevice;				//! directx (keyboard) inputdevice
	byte keybuffer[256];						//! currently pressed keys
	Logger logger;
};

#endif