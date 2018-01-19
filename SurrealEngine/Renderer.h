/*! \file  Renderer.h
\brief a abstract class from which renderering classes must inherit
*/

#ifndef RENDERER_H_
#define RENDERER_H_

#include <d3d9.h> // direct3d 
#include <string>

class Renderer
{
public:
	virtual ~Renderer();
	virtual bool Init(HWND, bool) = 0;				
	virtual void Clear(D3DCOLOR) = 0;						//gebruikt om back buffer frames te clearen
	virtual bool Begin() = 0;
	virtual void End() = 0;
	virtual void Present(HWND) = 0;

	virtual void Log(std::string, std::string) = 0;				//! lets the logger log an error, warning or info
	virtual void Flush() = 0;
};

#endif // RENDERER_H_