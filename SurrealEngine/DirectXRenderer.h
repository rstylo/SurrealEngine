/*! \file DirectXRender.h
	\brief This class is used for setting the render configuration for directx9 only
*/

#ifndef DIRECTXRENDERER_H_
#define DIRECTXRENDERER_H_

#include <d3d9.h> // direct3d 
#include "Renderer.h"
#include "Logger.h"
#include "DxManager.h"
#include "Transform.h"

#define FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE|D3DFVF_NORMAL)  //! flexible vertex format
#define FVF_TEXTUREDVERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1)										//! flexible vertex format

struct xyzTextureVertex
{
	//! terrain vertex with position, texture, diffuse color and normal.
	D3DXVECTOR3 position;
	FLOAT tu, tv;

	DWORD color;        // kleur
	D3DXVECTOR3 normal;

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


public:

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
	virtual void GetTextureDesc(std::string, D3DSURFACE_DESC*);

	// Vertex functions

	virtual bool LoadIndexedVertices(std::string, int _primCount, int _vertexCount, xyzTextureVertex * vertices, WORD * indices, int sizeOfVertices, int sizeOfIndices);
	virtual void DrawVertices(std::string);
	virtual void DrawVerticesBackground(std::string);
	virtual void UnLoadVertices(std::string);



private:
	LPDIRECT3DDEVICE9 device;					//! long pointer to d3d rendering device

	LPDIRECT3D9 direct3d;						//! d3d long pointer

	Logger logger;								//!	 Logger that tracks info, warnings, errors

	DxManager* dxManager;
};


#endif // !DIRECTXRENDERER_H_
