#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3d9.h>
#include <dinput.h>
#include "InputHandler.h"

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