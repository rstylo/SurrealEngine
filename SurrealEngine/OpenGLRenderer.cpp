/*
*	Placeholder to test for multiple different rendertypes
*/

#include "OpenGLRenderer.h"


OpenGLRenderer::OpenGLRenderer()
{
}


OpenGLRenderer::~OpenGLRenderer()
{
}

bool OpenGLRenderer::Init(HWND hWnd, bool windowed)
{
	return true;
}

void OpenGLRenderer::Clear(D3DCOLOR color)
{
}

bool OpenGLRenderer::Begin() {
	return true;
}

void OpenGLRenderer::End() {
}

void OpenGLRenderer::Present(HWND wnd) {
}

void OpenGLRenderer::Log(std::string, std::string)
{
}

void OpenGLRenderer::Flush()
{
}

