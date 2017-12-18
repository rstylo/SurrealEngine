#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>
#include <d3d9.h>
#include <dinput.h>
#include <map>

struct MouseValues {
	long x;
	long y;
	int dX;
	int dY;
	bool button0;
	bool button1;
};

class Mouse;
class Keyboard;
class Camera;

class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();


	virtual void SetWindow(HWND);
	virtual HWND* GetWindow();

	virtual void SaveReleaseDevice();
	virtual bool Init(HWND*);

	virtual bool CheckKeyboardPressed(char);
	virtual bool CheckMousePressed(int);


private:
	Keyboard* keyboard;
    Mouse* mouse;

	byte* keybuffer;
	MouseValues* mouseValues;

	HWND* CurrentWindow;
	LPDIRECTINPUT dInput;

	
};

#endif
