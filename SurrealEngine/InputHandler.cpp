#include "InputHandler.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Wnd.h"
#include "Camera.h"

InputHandler::InputHandler(HWND* wnd)
{
	if (Init()) {
		mouse = new Mouse(wnd);
		keyboard = new Keyboard(wnd, dInput);
	}
}


InputHandler::~InputHandler()
{
	keyboard->SaveReleaseDevice();
	delete keyboard;
}

void InputHandler::Acquire()
{
	mouse->DoAcquire();
	keyboard->DoAcquire();
}

/*bool InputHandler::GetKey(byte key)
{
	return keyboard->ProcessKBInput(key);
}*/

bool InputHandler::Init()
{
	//DirectInput8Create should be done only once in manager
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED(hr)
	{
		return false;
	}
	return true;
}

void InputHandler::Update(Camera* cam)
{
	switch (keyboard->CheckKeyPressed()) {
	case 'w':
		cam->MoveForwards();
		return;
	case 'a':
		cam->MoveLeft();
		return;
	case 's':
		cam->MoveBackwards();
		return;
	case 'd':
		cam->MoveRight();
		return;
	}

}
