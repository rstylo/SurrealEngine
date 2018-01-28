/*! \file DirectXRender.h
	\brief This class is used for setting the render configuration for directx9 only
*/

#ifndef DIRECTXRENDERER_H_
#define DIRECTXRENDERER_H_

#include <d3d9.h> // direct3d 
#include "Renderer.h"
#include "Logger.h"

class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer();
	virtual ~DirectXRenderer();

	virtual bool Init(HWND, bool);				//! initialise the renderer with a window and a boolean for if the window should be in windowed mode or not
	virtual void Clear(D3DCOLOR);				//! clear the backbuffer, before starting a new frame
	virtual bool Begin();						//! begin inserting into the backbuffer, start of a new frame
	virtual void End();							//! clear the backbuffer, end of a frame
	virtual void Present(HWND);					//! display the created backbuffer
	virtual LPDIRECT3DDEVICE9* GetDevice();		//! returns pointer to a long pointer of d3d rendering device 
	
	virtual void Log(std::string, std::string);	//! lets the logger log an error, warning or info
	virtual void Flush();						//! flushes the logger


private:
	LPDIRECT3DDEVICE9 device;					//! long pointer to d3d rendering device

	LPDIRECT3D9 direct3d;						//! d3d long pointer

	Logger logger;								//!	 Logger that tracks info, warnings, errors
};

#endif // RENDERER_H_#pragma once
