/*
* Class: Renderer.h
* Description : Class from witch renderer's must inherit from
* Note : this class doesnt have an actual implementation
*/

#ifndef RENDERER_H_
#define RENDERER_H_

#include <d3d9.h> // direct3d 

class Renderer
{
public:
	virtual ~Renderer();
	virtual bool Init(HWND, bool) = 0;				//params: handel device + in windowed of niet?
	virtual void Clear(D3DCOLOR) = 0;			 //gebruikt om back buffer frames te clearen
	virtual bool Begin() = 0;
	virtual void End() = 0;
	virtual void Present(HWND) = 0;
	virtual LPDIRECT3DDEVICE9* GetDevice() = 0;

};

#endif // RENDERER_H_