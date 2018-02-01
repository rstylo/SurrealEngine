/*! \file  Renderer.h
\brief a abstract class from which renderering classes must inherit
*/

#ifndef RENDERER_H_
#define RENDERER_H_

#include <windows.h>
#include <string>

struct Vector3 {
	float x, y, z;
	Vector3() {};
	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	};
};

struct xyzTextureVertex
{
	Vector3 position;
	FLOAT tu, tv;

	DWORD color;      
	Vector3 normal;

	xyzTextureVertex() {};
	xyzTextureVertex(float _x, float _y, float _z, FLOAT _u, FLOAT _v, DWORD _color) {
		position.x = _x;
		position.y = _y;
		position.z = _z;
		tu = _u;
		tv = _v;
		color = _color;
		normal = position;
	}
};


class Renderer
{
public:
	virtual ~Renderer();
	virtual bool Init(HWND, bool) = 0;				
	virtual void Clear(DWORD) = 0;						//gebruikt om back buffer frames te clearen
	virtual bool Begin() = 0;
	virtual void End() = 0;
	virtual void Present(HWND) = 0;

	virtual void Log(std::string, std::string) = 0;				//! lets the logger log an error, warning or info
	virtual void Flush() = 0;
	
	//Transform functions
	virtual void SetupMatrices(Vector3, Vector3) = 0;
	virtual void SetupMatrices(Vector3, Vector3, Vector3, Vector3) = 0;
	virtual void SetupMatricesRotate(Vector3) = 0;

	// HeightMap functions
	virtual bool LoadHeightMapWithBmp(std::string) = 0;
	virtual byte* GetHeightData(std::string) = 0;
	virtual int GetHeightMapWidth(std::string) = 0;
	virtual int GetHeightMapDepth(std::string) = 0;
	virtual int UnLoadHeightMap(std::string) = 0;

	// Mesh functions
	virtual bool LoadMesh(std::string) = 0;
	virtual void DrawMesh(std::string) = 0;
	virtual void UnLoadMesh(std::string) = 0;

	// Texture functions
	virtual bool LoadTexture(std::string) = 0;
	virtual void DrawTexture(std::string) = 0;
	virtual void UnLoadTexture(std::string) = 0;
	virtual float GetTextureWidth(std::string) = 0;
	virtual float GetTextureHeight(std::string) = 0;

	// Vertex functions

	virtual bool LoadIndexedVertices(std::string, int _primCount, int _vertexCount, xyzTextureVertex * vertices, WORD * indices, int sizeOfVertices, int sizeOfIndices) = 0;
	virtual void DrawVertices(std::string) = 0;
	virtual void DrawVerticesBackground(std::string) = 0;
	virtual void UnLoadVertices(std::string) = 0;

	//camera functions
	virtual void SetupView(float, float) = 0;

	//Lighting
	virtual void SetupLight() = 0;
	
};

#endif // RENDERER_H_