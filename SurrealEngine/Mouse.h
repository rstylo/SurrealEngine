/*! \file  Keyboard.h
\brief an extention of inputhandler that hold and gets mouse inputs
*/


#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3d9.h>
#include <dinput.h>
#include "InputHandler.h"

struct MouseValues {
	long x;
	long y;
	int dX;
	int dY;
	bool button0;
	bool button1;
};

class Mouse
{

public:
	Mouse(LPDIRECTINPUT);
	virtual ~Mouse();

	bool Init(HWND*);
	void SaveReleaseDevice();
	virtual bool SetWindow(HWND*);
	virtual bool DoAcquire();				
	virtual bool UpdateValues();
	virtual MouseValues* GetValues();

private:

	LPDIRECTINPUT dInput;
	LPDIRECTINPUTDEVICE dDevice;
	DIPROPDWORD dipdw;
	char mousebuffer[8];
	MouseValues mouseValues;

	DIDEVICEOBJECTDATA od[6];

};

#endif