#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

bool Input::Init()
{
	rawInput[0].usUsagePage = 0x01;	//keyboard en mouse hid
	rawInput[0].usUsage = 0x06;		//code voor te lezen device, keyboard in dit geval
	rawInput[0].dwFlags = 0;		//default, legacy n al
	rawInput[0].hwndTarget = 0;		//

	if (!SUCCEEDED(RegisterRawInputDevices(rawInput, 1, sizeof(rawInput[0]))))
	{
		return false;
	}

	return true;
}