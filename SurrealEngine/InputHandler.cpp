#include "InputHandler.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Wnd.h"
#include "Camera.h"
#include <cstdlib>
#include <iostream>

InputHandler::InputHandler()
{
	MouseValues* mouseValues = NULL;
}


InputHandler::~InputHandler()
{
	SaveReleaseDevice();
	if (keyboard != NULL)
	{
		delete keyboard;
		keyboard = NULL;
	}
	if (mouse != NULL)
	{
		delete mouse;
		mouse = NULL;
	}
}

bool InputHandler::Init(HWND* _hwnd)
{
	if FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL))
	{
		return false;
	}

	mouse = new Mouse(dInput);
	keyboard = new Keyboard(dInput);
	CurrentWindow = _hwnd;
	SetFocus(*_hwnd);
	if (!(mouse->Init(_hwnd) && keyboard->Init()))
	{
		printf("failed initializing keyboard/mouse");
		SaveReleaseDevice();
	}


	return true;
}

void InputHandler::Update()
{
	mouse->UpdateValues();
	keyboard->UpdateKeyBuffer();
}

void InputHandler::SetWindow(HWND* _hwnd)
{
	if (CurrentWindow != _hwnd) {
		mouse->SetWindow(_hwnd);
		keyboard->SetWindow(_hwnd);
		CurrentWindow = _hwnd;
	}
}

HWND * InputHandler::GetWindow()
{
	return CurrentWindow;
}

void InputHandler::SaveReleaseDevice()
{
	if (dInput)
	{
		mouse->SaveReleaseDevice();
		keyboard->SaveReleaseDevice();
		dInput->Release();
		dInput = NULL;
	}
}

bool InputHandler::CheckKeyboardPressed(char _key)
{
	switch (_key)
	{
	case 'a':
		return keyboard->CheckKeyPressed(DIK_A);
	case 's':
		return keyboard->CheckKeyPressed(DIK_S);
	case 'd':
		return keyboard->CheckKeyPressed(DIK_D);
	case 'w':
		return keyboard->CheckKeyPressed(DIK_W);
	case '.':
		return keyboard->CheckKeyPressed(DIK_SPACE);
	case 'c':
		return keyboard->CheckKeyPressed(DIK_C);
	case 'e':
		return keyboard->CheckKeyPressed(DIK_E);
	case 'q':
		return keyboard->CheckKeyPressed(DIK_Q);
	case '`':
		return keyboard->CheckKeyPressed(DIK_ESCAPE);
	}

	return false;
}

bool InputHandler::CheckMousePressed(int button)
{
	switch (button) {
	case 0:
		return mouse->GetValues()->button0;
	case 1:
		return mouse->GetValues()->button1;
	}
}

int InputHandler::CheckMouseValues(char position)
{
	switch (position) {
	case 'x':
		return mouse->GetValues()->dX;
	case 'y':
		return mouse->GetValues()->dY;
	}
	return 0;
}