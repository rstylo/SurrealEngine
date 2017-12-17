#include "InputHandler.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Wnd.h"
#include "Camera.h"
#include <cstdlib>
#include <iostream>

InputHandler::InputHandler(HWND* _wnd)
{
	amount = 0;
	window = 0;
	byte* keybuffer = NULL;
	MouseValues* mouseValues = NULL;
	

	if (Init()) {
		AddDevice(_wnd);
		currentWindow = _wnd;
		if (!(mouse[0]->Init() && keyboard[0]->Init()))
			SaveReleaseDevice();
	}
}


InputHandler::~InputHandler()
{
	SaveReleaseDevice();
	delete keyboard[0];
	keyboard[0] = NULL;
	delete mouse[0];
	mouse[0] = NULL;
}

void InputHandler::AddDevice(HWND* _wnd) {
	mouse[amount] = new Mouse(_wnd, dInput);
	keyboard[amount] = new Keyboard(_wnd, dInput);
	mouse[amount]->Init();
	keyboard[amount]->Init();
	mouseValues[amount] = mouse[amount]->getValues();
	keybuffer[amount] = keyboard[amount]->GetKeyBuffer();
	wnd[amount] = _wnd;
	SetFocus(*wnd[0]);
	amount++;
}

void InputHandler::SaveReleaseDevice()
{
	if (dInput)
	{
		mouse[0]->SaveReleaseDevice();
		keyboard[0]->SaveReleaseDevice();
		dInput->Release();
		dInput = NULL;
	}
}

bool InputHandler::Init()
{
	if FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL))
	{
		return false;
	}
	return true;
}

void InputHandler::Update(Camera* cam, int wndn)
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

void InputHandler::HandleKeys(Camera* cam,int wndn)
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
