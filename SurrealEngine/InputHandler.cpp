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

void InputHandler::SetWindow(HWND _hwnd) 
{
	if (CurrentWindow != &_hwnd) {
		mouse->SetWindow(&_hwnd);
		keyboard->SetWindow(&_hwnd);
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
















/*

MouseValues* InputHandler::Checkmouse(int wndn)
{
	if (mouse[window]->UpdateValues()) {
		return mouseValues[wndn];
	}
}


void InputHandler::CheckKey(char key, int wndn) {


}

void InputHandler::CheckKey(Char key, int wndn)
{
	//mouse handling
	if (mouse[window] != NULL) {
		if (mouse[window]->UpdateValues()) {
			HandleMouse(cam,wndn);
		}
	}
	GetFocus();

	//keyboard handling
	if (keyboard[window] != NULL) {
		if (keyboard[window]->CheckKeyPressed()) {
			HandleKeys(cam,wndn);
		}
	}
}

void InputHandler::HandleKeys(char key,int wndn)
{
	if (keybuffer[wndn][DIK_A] & 0x80)
		cam->MoveLeft();
	if (keybuffer[wndn][DIK_W] & 0x80)
		cam->MoveForwards();
	if (keybuffer[wndn][DIK_S] & 0x80)
		cam->MoveBackwards();
	if (keybuffer[wndn][DIK_D] & 0x80)
		cam->MoveRight();
	if (keybuffer[wndn][DIK_C] & 0x80)
		cam->MoveDown();

	if (keybuffer[wndn][DIK_UP] & 0x80)
		cam->MoveForwards();
	if (keybuffer[wndn][DIK_LEFT] & 0x80)
		cam->MoveLeft();
	if (keybuffer[wndn][DIK_RIGHT] & 0x80)
		cam->MoveRight();
	if (keybuffer[wndn][DIK_DOWN] & 0x80)
		cam->MoveBackwards();
	
	if (keybuffer[wndn][DIK_SPACE] & 0x80)
		cam->MoveUp();

	if (keybuffer[wndn][DIK_U] & 0x80)

	if (keybuffer[wndn][DIK_ESCAPE] & 0x80)
		exit(0);
}

void InputHandler::HandleMouse(Camera* cam, int wndn)
{
	cam->Rotate(0, mouseValues[wndn]->dX);
	if (mouseValues[wndn]->button0)
		cam->MoveForwards();
}



bool InputHandler::SetWnd(int _window)
{
	window = _window;
	return true;
}
*/