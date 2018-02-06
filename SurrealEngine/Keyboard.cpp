#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
	dDevice = NULL;

}

Keyboard::~Keyboard()
{
	SaveReleaseDevice();
}

bool Keyboard::Init(LPDIRECTINPUT dInput, HWND* _hwnd)
{
	//! initialise the inputdevice as a keyboard
	HRESULT hr = dInput->CreateDevice(GUID_SysKeyboard, &dDevice, NULL);
	if FAILED(hr)
	{
		printf("Failed creating a keyboard device");
		logger.Log("Failed creating a keyboard device", "Error");
		SaveReleaseDevice();
		return false;
	}

	hr = dDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
	{
		printf("Failed setting the keyboard data format");
		logger.Log("Failed setting the keyboard data format", "Error");
		SaveReleaseDevice();
		return false;
	}
	hr = dDevice->SetCooperativeLevel(*_hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr)
	{
		printf("Failed setting the keyboard cooperative level");
		logger.Log("Failed setting the keyboard cooperative level", "Error");
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
			printf("Failed setting the keyboard cooperative level");
			logger.Log("Failed setting the keyboard cooperative level", "Error");
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