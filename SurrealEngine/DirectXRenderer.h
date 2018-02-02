/*! \file DirectXRender.h
	\brief This class is used for setting the render configuration for directx9 only
*/

#ifndef DIRECTXRENDERER_H_
#define DIRECTXRENDERER_H_

#include <d3d9.h> // direct3d 
#include "Renderer.h"
#include "Logger.h"
#include "DxManager.h"

#define FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE|D3DFVF_NORMAL)  //! flexible vertex format
#define FVF_TEXTUREDVERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1)										//! flexible vertex format




class DirectXRenderer : public Renderer
{
public:


	DirectXRenderer();
	virtual ~DirectXRenderer();

	virtual bool Init(HWND, bool);				//! initialise the renderer with a window and a boolean for if the window should be in windowed mode or not
	virtual void Clear(DWORD);				//! clear the backbuffer, before starting a new frame
	virtual bool Begin();						//! begin inserting into the backbuffer, start of a new frame
	virtual void End();							//! clear the backbuffer, end of a frame
	virtual void Present(HWND);					//! display the created backbuffer
	virtual LPDIRECT3DDEVICE9* GetDevice();		//! returns pointer to a long pointer of d3d rendering device 
	
	virtual void Log(std::string, std::string);	//! lets the logger log an error, warning or info
	virtual void Flush();						//! flushes the logger


public:

	//Transform functions
	virtual void SetupMatrices(Vector3, Vector3);						//! setup world matrix with a position and rotation
	virtual void SetupMatrices(Vector3, Vector3, Vector3, Vector3); 	//! setup world matrix with a position and rotation relative to an other position and roation  
	virtual void SetupMatricesRotate(Vector3);							//! setuup world matrix with only a rotations

	// HeightMap functions
	virtual bool LoadHeightMapWithBmp(std::string);						//! load a heightmp with the given bitmap
	virtual byte* GetHeightData(std::string);							//! returns heightData of a already loaded heightmap 
	virtual int GetHeightMapWidth(std::string);							
	virtual int GetHeightMapDepth(std::string);
	virtual void UnLoadHeightMap(std::string);							//! delete a loaded heightmap and its data

	// Mesh functions
	virtual bool LoadMesh(std::string);									//! create a mesh with the a give meshPath
	virtual void DrawMesh(std::string);									//! draw mesh with the given meshpath if already loaded
	virtual void UnLoadMesh(std::string);								//! delete a mesh with the give meshpath and its data if already loaded

	// Texture functions
	virtual bool LoadTexture(std::string);								//! loads a texture with given texturepath	
	virtual void DrawTexture(std::string);								//! draws texture of given texturePath if already loaded
	virtual void UnLoadTexture(std::string);							//! delete a texture with a give texturepath if already loaded
	virtual float GetTextureWidth(std::string);							//! returns width of given texture
	virtual float GetTextureHeight(std::string);						//! returs height of given texture

	// Vertex functions

	virtual bool LoadIndexedVertices(std::string, int, int, xyzTextureVertex *, WORD *, int, int);	//! load new verticces with a name, primitiveCount, Vertexcount, *vertices array, *indices array, sizeOfvVertices, sizeOfIndices
	virtual void DrawVertices(std::string);														//! draw vertices with given name
	virtual void DrawVerticesBackground(std::string);											//! draw vertices with give name without zbuffer
	virtual void UnLoadVertices(std::string);													//! release vertex and indexbuffers to free space

	virtual void SetupView(float, float);														//! setup view with a nearplane and a farplane

	virtual void SetupLight();																	//! initialises light



private:
	LPDIRECT3DDEVICE9 device;					//! long pointer to d3d rendering device

	LPDIRECT3D9 direct3d;						//! d3d long pointer

	Logger logger;								//!	 Logger that tracks info, warnings, errors

	DxManager* dxManager;
};


#endif // !DIRECTXRENDERER_H_
