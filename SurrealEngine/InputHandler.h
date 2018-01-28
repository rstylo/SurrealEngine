/*! \file  InputHander.h
	\brief This class's main purpose is to get input from input devices

*/

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>
#include <d3d9.h>
#include <dinput.h>
#include "Logger.h"

class Mouse;					//mouse device
class Keyboard;					//keyboard device

class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();


	virtual void SetWindow(HWND*);				//! change the window that the input handler is focussed on
	virtual HWND* GetWindow();					//! get the window on which the inputhandler is focussed on

	virtual void SaveReleaseDevice();			
	virtual bool Init(HWND*);					//! initiae inputhandler with a starting window

	virtual void Update();						//! main routine, updates all input devices

	virtual bool CheckKeyboardPressed(char);	//! returns true when given character is pressed
	virtual bool CheckMousePressed(int);		//! returns true when give button is pressed
	virtual int CheckMouseValues(char);			//! returns a value depending on the give char x or y


private:
	Keyboard* keyboard;							//! keyboard device
	Mouse* mouse;								//! mouse device

	HWND* CurrentWindow;
	LPDIRECTINPUT dInput;

	Logger logger;

};

#endif