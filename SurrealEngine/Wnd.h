/*! \file  WND.h
	\brief this class is a wrapper class of the Windows window from windowsAPI, for creating windows on which view is to be displayed
*/

#ifndef WND_H_
#define WND_H_
#include <Windows.h>
#include <string>
#include <iostream>
#include "Logger.h"

class Wnd
{
public:
	Wnd(LPSTR, LPSTR, int, int); //! create with className, windowtitle and window sizes
	~Wnd();

	bool Init();				//! initialises on the middle of the screen, returns true if succesful
	bool Init(int, int);		//! initialise on a position, returns true if succesful
	bool IsInitialized();		
	bool Run();					//! update routine, returs true if window is still working
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	//! Message handling

public:
	HWND hWnd;
	MSG message;

private:
	HINSTANCE hInstance;
	int nCmdShow;
	LPSTR className;
	LPSTR windowTitle;
	int width;
	int height;
	//WPARAM wParam;
	//LPARAM lParam;
	bool initialized;
	Logger logger;
};

#endif // !WND_H_