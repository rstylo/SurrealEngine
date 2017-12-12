#include "Keyboard.h"
#include <iostream>

#define KEYDOWN(keybuffer, key) (keybuffer[key] & 0x80)

Keyboard::Keyboard(HWND* _wnd, LPDIRECTINPUT _dInput)
{
	dInput = _dInput;
	dDevice = NULL;
	wnd = _wnd;
	Init();
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
	if (dInput)
	{
		if (dDevice)
		{
			dDevice->Unacquire();
			dDevice->Release();
			dDevice = NULL;
		}
		dInput->Release();
		dInput = NULL;
	}
}


char Keyboard::CheckKeyPressed()
{
	DoAcquire();
	dDevice->GetDeviceState(sizeof(keybuffer), (LPVOID)&keybuffer);
	if (keybuffer[DIK_A] & 0x80)
		return 'a';
	if (keybuffer[DIK_W] & 0x80)
		return 'w';
	if (keybuffer[DIK_S] & 0x80)
		return 's';
	if (keybuffer[DIK_D] & 0x80)
		return 'd';
	if (keybuffer[DIK_UP] & 0x80)
		return 'w';
	if (keybuffer[DIK_LEFT] & 0x80)
		return 'a';
	if (keybuffer[DIK_RIGHT] & 0x80)
		return 'd';
	if (keybuffer[DIK_DOWN] & 0x80)
		return 'd';
	return NULL;
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