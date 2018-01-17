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

	virtual bool Init(HWND, bool);				//params: handel device + in windowed of niet?
	virtual void Clear(D3DCOLOR);			 //gebruikt om back buffer frames te clearen
	virtual bool Begin();
	virtual void End();
	virtual void Present(HWND);
	//virtual LPDIRECT3DDEVICE9* GetDevice();


private:
	//LPDIRECT3DDEVICE9 device;					//(staat voor long pointer naar d3d device),  de rendering device
												//weet de voordelen er niet van over "normale" pointer(IDirect3DDevice9* device), alleen dat het een gedoe om het te deleten
												//daarom is het fijn dat om deze manier met ->Release of ->reset pointer vrij gemaakt kan worden..

	//LPDIRECT3D9 direct3d;						//direct3d zlf, dus hier kan ook LPDIRECT3D9* direct3d, wordt met name gebruikt om direct x te initialiseren

};

#endif // RENDERER_H_#pragma once
