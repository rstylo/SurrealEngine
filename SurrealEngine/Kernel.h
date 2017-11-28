#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <d3d9.h>

LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID Cleanup();
VOID Render();

class Kernel {

public:
	Kernel();
	virtual ~Kernel();
	HRESULT InitD3D(HWND hWnd, HWND hWnd2);
	
private:
	
};

#endif