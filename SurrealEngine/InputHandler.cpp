#include "InputHandler.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Wnd.h"
#include "Camera.h"
#include <cstdlib>

InputHandler::InputHandler(HWND* wnd)
{
	byte* keybuffer = NULL;
	MouseValues* mouseValues = NULL;
	if (Init()) {
		mouse = new Mouse(wnd, dInput);
		keyboard = new Keyboard(wnd, dInput);
		if (!(mouse->Init() && keyboard->Init()))
			SaveReleaseDevice();
	}
}


InputHandler::~InputHandler()
{
	SaveReleaseDevice();
	delete keyboard;
	delete mouse;
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

void InputHandler::Acquire()
{
	mouse->DoAcquire();
	keyboard->DoAcquire();
}

bool InputHandler::Init()
{
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED(hr)
	{
		return false;
	}
	return true;
}

void InputHandler::Update(Camera* cam)
{
	//keyboard handling
	keybuffer = keyboard->CheckKeyPressed();
	
	HandleKeys(cam);
	// mouse handling
	mouseValues = mouse->UpdateValues();

	HandleMouse(cam);
	
}

void InputHandler::HandleKeys(Camera* cam)
{
	if (keybuffer[DIK_A] & 0x80)
		cam->MoveLeft();
	if (keybuffer[DIK_W] & 0x80)
		cam->MoveForwards();
	if (keybuffer[DIK_S] & 0x80)
		cam->MoveBackwards();
	if (keybuffer[DIK_D] & 0x80)
		cam->MoveRight();
	if (keybuffer[DIK_C] & 0x80)
		cam->MoveDown();

	if (keybuffer[DIK_UP] & 0x80)
		cam->MoveForwards();
	if (keybuffer[DIK_LEFT] & 0x80)
		cam->MoveLeft();
	if (keybuffer[DIK_RIGHT] & 0x80)
		cam->MoveRight();
	if (keybuffer[DIK_DOWN] & 0x80)
		cam->MoveBackwards();
	
	if (keybuffer[DIK_SPACE] & 0x80)
		cam->MoveUp();
	
	if (keybuffer[DIK_ESCAPE] & 0x80) {
		exit(0);
	}
}

void InputHandler::HandleMouse(Camera* cam)
{
	cam->Rotate(0, mouseValues->dX);
	if (mouseValues->button0)
		cam->MoveForwards();
}
