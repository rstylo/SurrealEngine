#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard(HWND* _wnd, LPDIRECTINPUT _dInput)
{
	dInput = _dInput;
	dDevice = NULL;
	wnd = _wnd;
}

Keyboard::~Keyboard()
{
}

bool Keyboard::Init()
{
	HRESULT hr = dInput->CreateDevice(GUID_SysKeyboard, &dDevice, NULL);
	if FAILED(hr)
	{
		SaveReleaseDevice();
		return false;
	}

	hr = dDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
	{
		SaveReleaseDevice();
		return false;
	}

	hr = dDevice->SetCooperativeLevel(*wnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr)
	{
		SaveReleaseDevice();
		return false;
	}
	return true;
}

void Keyboard::SaveReleaseDevice()
{
	if (dDevice)
	{
		dDevice->Unacquire();
		dDevice->Release();
		dDevice = NULL;
	}
}


byte* Keyboard::CheckKeyPressed()
{
	
	if(FAILED(dDevice->GetDeviceState(sizeof(keybuffer), (LPVOID)&keybuffer)));
		DoAcquire();
	return keybuffer;
}

bool Keyboard::DoAcquire()
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