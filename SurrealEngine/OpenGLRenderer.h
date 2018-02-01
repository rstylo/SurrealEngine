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
	virtual void Clear(DWORD);

	virtual bool Begin();
	virtual void End();
	virtual void Present(HWND);
	virtual void Log(std::string, std::string);
	virtual void Flush();

	//Transform functions
	virtual void SetupMatrices(Vector3, Vector3);
	virtual void SetupMatrices(Vector3, Vector3, Vector3, Vector3);
	virtual void SetupMatricesRotate(Vector3);

	// HeightMap functions
	virtual bool LoadHeightMapWithBmp(std::string);
	virtual byte* GetHeightData(std::string);
	virtual int GetHeightMapWidth(std::string);
	virtual int GetHeightMapDepth(std::string);
	virtual int UnLoadHeightMap(std::string);

	// Mesh functions
	virtual bool LoadMesh(std::string);
	virtual void DrawMesh(std::string);
	virtual void UnLoadMesh(std::string);

	// Texture functions
	virtual bool LoadTexture(std::string);
	virtual void DrawTexture(std::string);
	virtual void UnLoadTexture(std::string);
	virtual float GetTextureWidth(std::string);
	virtual float GetTextureHeight(std::string);

	// Vertex functions

	virtual bool LoadIndexedVertices(std::string, int _primCount, int _vertexCount, xyzTextureVertex * vertices, WORD * indices, int sizeOfVertices, int sizeOfIndices);
	virtual void DrawVertices(std::string);
	virtual void DrawVerticesBackground(std::string);
	virtual void UnLoadVertices(std::string);

	virtual void SetupView(float, float);

	virtual void SetupLight();
private:

};

#endif