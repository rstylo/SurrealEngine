#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include <d3d9.h>

class Window {

public:
	Window(WNDCLASSEX, LPCWSTR, int, int, int, int);
	virtual ~Window();


private:
	HWND window;

};

#endif