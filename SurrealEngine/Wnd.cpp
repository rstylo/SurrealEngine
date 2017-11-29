//#include "stdafx.h"
#include "Wnd.h"


LRESULT CALLBACK Wnd::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return 0;
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);																	//anders default window procedure
}

Wnd::Wnd(HINSTANCE hInstance, int nCmdShow, LPSTR className, LPSTR windowTitle, int width, int height)
	:hInstance(hInstance), nCmdShow(nCmdShow), className(className), windowTitle(windowTitle), width(width), height(height)
{
}


Wnd::~Wnd()
{

}

bool Wnd::Init() 
{
	WNDCLASSEX windowClassEx;																									//window classs ex(windows class maar met meer functionaliteit)

	ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

	windowClassEx.cbSize = sizeof(windowClassEx);
	windowClassEx.style = CS_HREDRAW | CS_VREDRAW;																				//redraw de window in elke size verandering
	windowClassEx.hInstance = hInstance;																						//de instance die vanuint main is mee gestuurd
	windowClassEx.lpfnWndProc = DefWindowProc;																						//message handling

	windowClassEx.lpszClassName = className;																					//naam van de window

	windowClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;																			//background kleur.. De variablen hierboven zijn nodig om de window te kunnen cre�ren

	windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);																		//default arrow
	windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);																		//default aplication icon
	windowClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);																			//default small icon

	if (RegisterClassEx(&windowClassEx) == false)																				//is klasse ex geregistreed?
	{
		initialized = false;
		MessageBox(NULL,"Failed creating window!!", NULL, NULL);
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) - width), (GetSystemMetrics(SM_CYSCREEN) - height), width, height, NULL, NULL, hInstance, NULL);	//window zelf cre�ren

	ShowWindow(hWnd, nCmdShow);																									//parameters voor hoe de window afgespeeld wordt

	initialized = true;
	return true;
}

bool Wnd::IsInitialized() 
{
	return initialized;
}

void Wnd::Run()
{
	if (initialized == true)	//maak nieuwe window aan
	{


		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))										//bekijk de message, peekMessage zal niet wachten voor een input, GetMessage zal nmlijk wel wachten
		{
			TranslateMessage(&message);																//vertalen virtual key messages naar character messages

			DispatchMessage(&message);																//call naar window procedure functie
		}

		if (message.message == WM_QUIT)
		{

		}
	}
}
