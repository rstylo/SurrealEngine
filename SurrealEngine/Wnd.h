#ifndef WND_H_
#define WND_H_
#include <Windows.h>


class Wnd
{
public:
	Wnd(HINSTANCE hInstance, int, LPSTR, LPSTR, int, int);
	~Wnd();

	bool Init();
	bool IsInitialized();
	void Run();
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
	WPARAM wParam;
	LPARAM lParam;

	bool initialized;
};

#endif // !WND_H_
