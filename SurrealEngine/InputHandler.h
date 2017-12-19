#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>
#include <d3d9.h>
#include <dinput.h>
#include <map>

class Mouse;
class Keyboard;
class Camera;

class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();


	virtual void SetWindow(HWND*);
	virtual HWND* GetWindow();

	virtual void SaveReleaseDevice();
	virtual bool Init(HWND*);

	virtual void Update();

	virtual bool CheckKeyboardPressed(char);
	virtual bool CheckMousePressed(int);
	virtual int CheckMouseValues(char);


private:
	Keyboard* keyboard;
    Mouse* mouse;

	HWND* CurrentWindow;
	LPDIRECTINPUT dInput;

	
};

#endif
