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
	SaveReleaseDevice();
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


bool Keyboard::CheckKeyPressed()
{
	if (FAILED(dDevice->GetDeviceState(sizeof(keybuffer), (LPVOID)&keybuffer))) {
		DoAcquire();
		if (FAILED(dDevice->GetDeviceState(sizeof(keybuffer), (LPVOID)&keybuffer)))
			return true;
	}
	return false;
}

byte* Keyboard::GetKeyBuffer()
{
	return keybuffer;
}

bool Keyboard::DoAcquire()
{	
	for (int i = 0; i < 5; i++)
	{
		if (SUCCEEDED(dDevice->Acquire()))
		{
			return true;
		}
	}
	return false;

}