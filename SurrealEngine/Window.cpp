#include "Window.h"

Window::Window(WNDCLASSEX wnd, LPCWSTR name, int x, int y, int height, int width)
{
	RegisterClassEx(&wnd);
	window = CreateWindow(L"Engine", name,
		WS_OVERLAPPEDWINDOW, x, y, height, width,
		NULL, NULL, wnd.hInstance, NULL);
	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

Window::~Window()
{
}

