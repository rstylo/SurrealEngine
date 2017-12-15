#ifndef MOUSE_H_
#define MOUSE_H_

#include <d3d9.h>
#include <dinput.h>
#include "InputHandler.h"

class Mouse
{
	

public:
	Mouse(HWND*, LPDIRECTINPUT);
	virtual ~Mouse();

	bool Init();
	void SaveReleaseDevice();
	virtual bool DoAcquire();
	MouseValues* UpdateValues();
private:
	HWND* wnd;
	LPDIRECTINPUT dInput;
	LPDIRECTINPUTDEVICE dDevice;
	DIPROPDWORD dipdw;
	char mousebuffer[8];
	MouseValues mouseValues;

	DIDEVICEOBJECTDATA od[6];
};

#endif