#ifndef _KERNEL_H_
#define _KERNEL_H_

#define MAXWINDOWS 10

#include <d3d9.h>
#include "Window.h"

LRESULT WINAPI MessageHandler(HWND , UINT , WPARAM , LPARAM);
VOID Cleanup();
VOID Render();

class Kernel {

public:
	Kernel();
	virtual ~Kernel();
	HRESULT InitD3D(HWND, LPDIRECT3DDEVICE9*);
	
private:
	Window* w1[MAXWINDOWS];
	
};

#endif