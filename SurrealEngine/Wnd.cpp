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
	/*case WM_INPUT:
	{
		UINT dwSize;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

		LPBYTE byte = new BYTE[dwSize];
		if (byte = NULL)
		{
			return 0;
		}

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, byte, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT* raw = (RAWINPUT*)byte;

		if (raw->header.dwType == RIM_TYPEKEYBOARD)
			if (raw->data.keyboard.Message == WM_KEYDOWN || (raw->data.keyboard.Message == WM_SYSKEYDOWN))
			{
				printf("key %d was pressed! \n", std::to_string(raw->data.keyboard.VKey));
			}
	}*/
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);																	//anders default window procedure
}

Wnd::Wnd(LPSTR className, LPSTR windowTitle, int width, int height)
	:hInstance(GetModuleHandle(0)), nCmdShow(SW_SHOWDEFAULT), className(className), windowTitle(windowTitle), width(width), height(height)
{
}


Wnd::~Wnd()
{
	UnregisterClass(className, hInstance);
}

bool Wnd::Init()
{
	return Init((GetSystemMetrics(SM_CXSCREEN) - width), (GetSystemMetrics(SM_CYSCREEN) - height));
}

bool Wnd::Init(int startX, int startY) 
{
	WNDCLASSEX windowClassEx;																									//window classs ex(windows class maar met meer functionaliteit)

	ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

	windowClassEx.cbSize = sizeof(windowClassEx);
	windowClassEx.style = CS_HREDRAW | CS_VREDRAW;																				//redraw de window in elke size verandering
	windowClassEx.hInstance = hInstance;																						//de instance die vanuint main is mee gestuurd
	windowClassEx.lpfnWndProc = DefWindowProc;																						//message handling

	windowClassEx.lpszClassName = className;																					//naam van de window

	windowClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;																			//background kleur.. De variablen hierboven zijn nodig om de window te kunnen creëren

	windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);																		//default arrow
	windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);																		//default aplication icon
	windowClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);																			//default small icon

	if (RegisterClassEx(&windowClassEx) == false)																				//is klasse ex geregistreed?
	{
		initialized = false;
		MessageBox(NULL,"Failed creating window!!", NULL, NULL);
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPEDWINDOW, startX, startY, width, height, NULL, NULL, hInstance, NULL);	//window zelf creëren

	ShowWindow(hWnd, nCmdShow);																									//parameters voor hoe de window afgespeeld wordt
	UpdateWindow(hWnd);

	initialized = true;
	return true;
}

bool Wnd::IsInitialized() 
{
	return initialized;
}

bool Wnd::Run()
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
			return false;
		}
		return true;
	}
	return false;
}

