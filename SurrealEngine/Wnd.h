#ifndef WND_H_
#define WND_H_
#include <Windows.h>
#include <string>
#include <iostream>

class Wnd
{
public:
	Wnd(LPSTR, LPSTR, int, int);
	~Wnd();

	bool Init();
	bool Init(int, int);
	bool IsInitialized();
	bool Run();
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);															//Functie voor message handling, wParam n lParam ... extra information dat niet perce nodig is

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
};

#endif // !WND_H_