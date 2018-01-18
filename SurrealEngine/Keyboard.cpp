#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard(LPDIRECTINPUT _dInput)
{
	dInput = _dInput;
	dDevice = NULL;

}

Keyboard::~Keyboard()
{
	SaveReleaseDevice();
}

bool Keyboard::Init()
{
	//! initialise keyboard
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
	return true;
}

bool Keyboard::SetWindow(HWND* _hwnd)
{
	//! set the focus window
	if (dDevice != NULL) {
		dDevice->Unacquire();
		if (!SUCCEEDED(dDevice->SetCooperativeLevel(*_hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			SaveReleaseDevice();
			return false;
		}

		return true;
	}
	return false;
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

bool Keyboard::UpdateKeyBuffer()
{
	//! update currently pressed keys information 
	if (dDevice != NULL)
	{
		if (!SUCCEEDED(dDevice->GetDeviceState(sizeof(keybuffer), (LPVOID)&keybuffer))) {
			DoAcquire();
			if (!SUCCEEDED(dDevice->GetDeviceState(sizeof(keybuffer), (LPVOID)&keybuffer)))
				return false;
		}
	}
	return true;
}


bool Keyboard::CheckKeyPressed(byte _key)
{
	if (keybuffer[_key] & 0x80)
		return true;
	else
		return false;
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