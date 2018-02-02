/*! \file  Keyboard.h
\brief an extention of inputhandler that hold and gets mouse inputs
*/

#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3d9.h>
#include <dinput.h>
#include "Logger.h"

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
	Mouse(LPDIRECTINPUT);					//! create with directxinput
	virtual ~Mouse();

	bool Init(HWND*);						//! initialise with window window
	void SaveReleaseDevice();
	virtual bool SetWindow(HWND*);			//! set currently focused window
	virtual bool DoAcquire();				//! acquire input
	virtual bool UpdateValues();			//! update routine
	virtual MouseValues* GetValues();		//! returns mouse values

private:

	LPDIRECTINPUT dInput;
	LPDIRECTINPUTDEVICE dDevice;
	DIPROPDWORD dipdw;
	char mousebuffer[8];					
	MouseValues mouseValues;			//! hold current mouse values

	DIDEVICEOBJECTDATA od[6];

	Logger logger;

};

#endif