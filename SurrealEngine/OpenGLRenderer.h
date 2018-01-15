/*
* Class: OpenGLRender.h
* Description: This class is used setting the render configuration
* Note : This is a directx class only
*/

#ifndef OPENGLRENDERER_H_
#define OPENGLRENDERER_H_

#include "Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	virtual bool Init(HWND, bool);				
	virtual void Clear(D3DCOLOR);
	virtual bool Begin();
	virtual void End();
	virtual void Present(HWND);
	//virtual LPDIRECT3DDEVICE9* GetDevice();


private:
};

#endif 
