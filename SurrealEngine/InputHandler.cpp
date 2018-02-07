#include "InputHandler.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Wnd.h"


InputHandler::InputHandler()
{
	MouseValues* mouseValues = NULL;
}


InputHandler::~InputHandler()
{
	//! release devices to free space
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
	//! initialise input handler with a window that needs to focussed on to get input
	if FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL))
	{
		printf("failed creating a directInput device\n");
		logger.Log("Failed creating a directInput device", "Error");
		return false;
	}

	mouse = new Mouse(dInput);
	keyboard = new Keyboard(dInput);
	CurrentWindow = _hwnd;
	SetFocus(*_hwnd);
	if (!(mouse->Init(_hwnd) && keyboard->Init()))
	{
		printf("failed initializing keyboard/mouse\n");
		logger.Log("Failed initializing keyboard/mouse", "Error");
		SaveReleaseDevice();
	}

	printf("Initialized the mouse and keyboard\n");
	logger.Log("Initialized the mouse and keyboard", "Info");
	return true;
}

void InputHandler::Update()
{
	//! update mouse and keyboard values
	mouse->UpdateValues();
	keyboard->UpdateKeyBuffer();
}

void InputHandler::SetWindow(HWND* _hwnd)
{
	//! change the focus window
	if (CurrentWindow != _hwnd) {
		mouse->SetWindow(_hwnd);
		keyboard->SetWindow(_hwnd);
		CurrentWindow = _hwnd;
	}
}

HWND * InputHandler::GetWindow()
{
	//! returns the currently set focus window
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
	//! returns true if specific char key is pressed
	switch (_key)
	{
	case 'a':
		return keyboard->CheckKeyPressed(DIK_A);
	case 'b':
		return keyboard->CheckKeyPressed(DIK_B);
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
	case 'h':
		return keyboard->CheckKeyPressed(DIK_H);
	case '`':
		return keyboard->CheckKeyPressed(DIK_ESCAPE);	
	}

	return false;
}

bool InputHandler::CheckMousePressed(int button)
{

	//! returb true if corresponding button is pressed, 0 for left click and 1 for right click
	switch (button) {
	case 0:
		return mouse->GetValues()->button0;
	case 1:
		return mouse->GetValues()->button1;
	}
}

int InputHandler::CheckMouseValues(char position)
{
	//! returns mouse x or y
	switch (position) {
	case 'x':
		return mouse->GetValues()->dX;
	case 'y':
		return mouse->GetValues()->dY;
	}
	return 0;
}