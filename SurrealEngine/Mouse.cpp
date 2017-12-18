#include "Mouse.h" 
#include <iostream>

Mouse::Mouse(LPDIRECTINPUT _dInput)
{
	mouseValues = { 0, 0, 0, 0, false, false };
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 8;
	dInput = _dInput;
	dDevice = NULL;
}


Mouse::~Mouse()
{
	SaveReleaseDevice();
}

bool Mouse::Init(HWND* _hwnd) {
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

	if (!SUCCEEDED(dDevice->SetCooperativeLevel(*_hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		SaveReleaseDevice();
		return false;
	}

	result = dDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

bool Mouse::SetWindow(HWND* _hwnd)
{
	if(dDevice != NULL)
	if(!SUCCEEDED(dDevice->SetCooperativeLevel(*_hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		SaveReleaseDevice();
		return false;
	}

	return true;
}

bool Mouse::UpdateValues() {
	DWORD elements = 6;
	mouseValues.dX = 0;
	mouseValues.dY = 0;

	if (FAILED(dDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), od, &elements, 0))) {
		mouseValues.button0 = false;
		mouseValues.button1 = false;
		DoAcquire();
		if (FAILED(dDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), od, &elements, 0)))
			return false;
	}

	for (int i = 0; i < elements; i++) {
		if (od[i].dwOfs == DIMOFS_X) {
			mouseValues.x += static_cast<long>(od[i].dwData);
			mouseValues.dX = static_cast<long>(od[i].dwData);
		}
		if (od[i].dwOfs == DIMOFS_Y) {
			mouseValues.y += static_cast<long>(od[i].dwData);
			mouseValues.dY = static_cast<long>(od[i].dwData);
		}
		if (od[i].dwOfs == DIMOFS_BUTTON0) {
			mouseValues.button0 = (od[i].dwData & 0x80) ? true : false;
		}
		if (od[i].dwOfs == DIMOFS_BUTTON1) {
			mouseValues.button1 = (od[i].dwData & 0x80) ? true : false;
		}
	}
	
	return true;
	
}

MouseValues * Mouse::getValues()
{
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
	for (int i = 0; i < 5; i++)
	{
		if (SUCCEEDED(dDevice->Acquire()))
		{
			return true;
		}
	}
	return false;
}
