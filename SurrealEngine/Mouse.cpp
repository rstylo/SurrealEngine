#include "Mouse.h"
#include <iostream>

Mouse::Mouse(HWND* _wnd, LPDIRECTINPUT _dInput)
{
	mouseValues = { 0, 0, 0, 0, false, false };
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 8;
	wnd = _wnd;
	dInput = _dInput;
	dDevice = NULL;
}


Mouse::~Mouse()
{
}

bool Mouse::Init() {
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = dInput->CreateDevice(GUID_SysMouse, &dDevice, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = dDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	result = dDevice->SetCooperativeLevel(*wnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result))
	{
		return false;
	}

	result = dDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}


MouseValues* Mouse::UpdateValues() {
	DWORD elements = 1;
	DIDEVICEOBJECTDATA od;
	
	if (FAILED(dDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0))) {
		mouseValues.dX = 0;
		mouseValues.dY = 0;
		mouseValues.button0 = false;
		mouseValues.button1 = false;
		DoAcquire();
		dDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0);
	}
		

	switch (od.dwOfs)
	{
	case DIMOFS_X:
		mouseValues.x += static_cast<long>(od.dwData);
		mouseValues.dX = static_cast<long>(od.dwData);
		break;
	case DIMOFS_Y:
		mouseValues.y += static_cast<long>(od.dwData);
		mouseValues.dY = static_cast<long>(od.dwData);
		break;
	case DIMOFS_BUTTON0:
		mouseValues.button0 = (static_cast<long>(od.dwData) == 0) ? false : true;
		break;
	case DIMOFS_BUTTON1:
		mouseValues.button1 = (static_cast<long>(od.dwData) == 0) ? false : true;
		break;
	}
	return &mouseValues;
	
}

void Mouse::SaveReleaseDevice()
{
	if (dDevice)
	{
		dDevice->Unacquire();
		dDevice->Release();
		dDevice = NULL;
	}
}

bool Mouse::DoAcquire()
{
	int times = 5;
	for (int i = 0; i < times; i++)
	{
		if (SUCCEEDED(dDevice->Acquire()))
		{
			return true;
		}
	}
	return false;
}
