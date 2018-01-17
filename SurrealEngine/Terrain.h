/*! \file  Terrain.h
	\brief this class is used to draw and move the terrain
*/


#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <d3dx9.h>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <cmath>
#include "Transform.h"

#define FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE|D3DFVF_NORMAL) //! flexible vertex format
#define FVF_TEXTUREDVERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1)										//! flexible vertex format




class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual void SetMapAndTexture(std::string heightMapFileName, std::string _textureName);		//! change heightmap and texture
	virtual bool Init(Renderer*);																//! initialise
	virtual void Invalidate();																	//! release the vertex buffer and indexBuffer to free space


	virtual void SetupMatrices(Renderer*, Transform);											//! setup position in which terrain is to be drawn
	//virtual bool InitWithColor(Renderer*);
	virtual void Draw(Renderer*);																

	virtual std::string GetMapFileName();														
	virtual std::string GetTextureName();

	Transform transform;
private:

	virtual void CleanUp();
	virtual bool LoadBMP(std::string);															//! get heightdata from a grayscale map

	std::string heightMapFileName;
	std::string textureName;
	
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;															
	LPDIRECT3DINDEXBUFFER9 indexBuffer;																
	
	LPDIRECT3DTEXTURE9 texture;
	
	BYTE* heightData;

	

	bool initialized;

	int width;
	int depth;
	int primCount;
	int vertexCount;


};


#endif // !TERRAIN_H_
