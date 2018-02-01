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

void OpenGLRenderer::Clear(DWORD color)
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

void OpenGLRenderer::SetupMatrices(Vector3, Vector3)
{
}

void OpenGLRenderer::SetupMatrices(Vector3, Vector3, Vector3, Vector3)
{
}

void OpenGLRenderer::SetupMatricesRotate(Vector3)
{
}

bool OpenGLRenderer::LoadHeightMapWithBmp(std::string)
{
	return false;
}

byte * OpenGLRenderer::GetHeightData(std::string)
{
	return nullptr;
}

int OpenGLRenderer::GetHeightMapWidth(std::string)
{
	return 0;
}

int OpenGLRenderer::GetHeightMapDepth(std::string)
{
	return 0;
}

int OpenGLRenderer::UnLoadHeightMap(std::string)
{
	return 0;
}

bool OpenGLRenderer::LoadMesh(std::string)
{
	return false;
}

void OpenGLRenderer::DrawMesh(std::string)
{
}

void OpenGLRenderer::UnLoadMesh(std::string)
{
}

bool OpenGLRenderer::LoadTexture(std::string)
{
	return false;
}

void OpenGLRenderer::DrawTexture(std::string)
{
}

void OpenGLRenderer::UnLoadTexture(std::string)
{
}

float OpenGLRenderer::GetTextureWidth(std::string)
{
	return 0.0f;
}

float OpenGLRenderer::GetTextureHeight(std::string)
{
	return 0.0f;
}

bool OpenGLRenderer::LoadIndexedVertices(std::string, int _primCount, int _vertexCount, xyzTextureVertex * vertices, WORD * indices, int sizeOfVertices, int sizeOfIndices)
{
	return false;
}

void OpenGLRenderer::DrawVertices(std::string)
{
}

void OpenGLRenderer::DrawVerticesBackground(std::string)
{
}

void OpenGLRenderer::UnLoadVertices(std::string)
{
}

void OpenGLRenderer::SetupView(float, float)
{
}

void OpenGLRenderer::SetupLight()
{
}

