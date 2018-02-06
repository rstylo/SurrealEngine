/*! \file  Keyboard.h
\brief an extention of inputhandler that hold and gets mouse inputs
*/

#ifndef MOUSE_H_
#define MOUSE_H_

#include <dinput.h>
#include "Logger.h"

//! Struct in which the values read from the mouse are stored in
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
	Mouse();
	virtual ~Mouse();

	bool Init(LPDIRECTINPUT, HWND*);		//! Creates a mouse inputdevice and links it with the window
	void SaveReleaseDevice();
	virtual bool SetWindow(HWND*);			//!	Links the mouse inputdevice with a different window
	virtual bool DoAcquire();				//!	Checks if there is a mouse connected
	virtual bool UpdateValues();			//!	Updates the values read from the mouse into the MouseValues struct
	virtual MouseValues* GetValues();		//! Returns the values stored in MouseValues update after the UpdateValues function

private:
	LPDIRECTINPUTDEVICE dDevice;			//!	DirectX (mouse) inputdevice 
	DIPROPDWORD dipdw;						
	MouseValues mouseValues;				//! Buffer where the mouse data is stored in

	DIDEVICEOBJECTDATA od[6];

	Logger logger;

};

#endif