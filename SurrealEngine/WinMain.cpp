
#include <Windows.h>
#include <iostream>
#include <string>

/*
* 1. Om de code te kunnen runnen, moet onder project properties -> vc++ -> included directories deze path toevoegen
* 	C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include.
* 2. vc++ -> liblary directiories
* 	C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86
* 3. daarna onder properties -> linker -> input -> Addiotional dependencies d3d9.lib en d3dx9.lib bij schrijven
* 4. verder  is het belangrijk dat het project op multi-bit rund anders werken LPSTR niet voor sommige van de windows functies
voeg hier * voor uncomment>/

bool MakeWindow(HINSTANCE hInstance, int nCmdShow, LPSTR className, HWND& hWnd, LPSTR windowTitle, int width, int height, int x, int y);	//paramaters die voor grootste deel bepaald worden door de gebruiker, behalve de eerste drie die mee krijgt vam de main

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);															//Functie voor message handling, wParam n lParam ... extra information dat niet perce nodig is

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)												//windows main function, geeft nodige parameters mee om een window te kunnen creeëren, previnstance altijd null!!
{

	HWND hWnd;																							//window class

	if (MakeWindow(hInstance, nCmdShow, "Mainwindow", hWnd, "First window :D", 1280, 720, 180, 180))	//maak nieuwe window aan
	{
		MSG message;

		while (1)
		{
			while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))										//bekijk de message, peekMessage zal niet wachten voor een input, GetMessage zal nmlijk wel wachten
			{
				TranslateMessage(&message);																//vertalen virtual key messages naar character messages

				DispatchMessage(&message);																//call naar window procedure functie
			}

			if (message.message == WM_QUIT)
				break;
			else																						//als de message geen quit is dan functies op roepen
			{

			}

		}

		return message.wParam;
	}


	return 0;

}

bool MakeWindow(HINSTANCE hInstance, int nCmdShow, LPSTR className, HWND& hWnd, LPSTR windowTitle, int width, int height, int x, int y)
{
	//WNDCLASS windowClass																										//geen size en icon
	WNDCLASSEX windowClassEx;																									//window classs ex(windows class maar met meer functionaliteit)

	ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

	windowClassEx.cbSize = sizeof(windowClassEx);
	windowClassEx.style = CS_HREDRAW | CS_VREDRAW;																				//redraw de window in elke size verandering
	windowClassEx.hInstance = hInstance;																						//de instance die vanuint main is mee gestuurd
	windowClassEx.lpfnWndProc = WindowProc;																						//message handling

	windowClassEx.lpszClassName = className;																					//naam van de window

	windowClassEx.hbrBackground = (HBRUSH)COLOR_WINDOW;																			//background kleur.. De variablen hierboven zijn nodig om de window te kunnen creëren

	windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);																		//default arrow
	windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);																		//default aplication icon
	windowClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);																			//default small icon

	if (RegisterClassEx(&windowClassEx) == false)																				//is klasse ex geregistreed?
	{
		MessageBox(NULL, "Failed creating window!!", NULL, NULL);
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);	//window zelf creëren

	ShowWindow(hWnd, nCmdShow);																									//parameters voor hoe de window afgespeeld wordt

	return true;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

	return DefWindowProc(hWnd, message, wParam, lParam);			//anders default window procedure
}


/**/