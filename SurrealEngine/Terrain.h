/*
* Class: Terrain.h
* Description :
* Note :
*/

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <d3dx9.h>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include "Transform.h"

#define FVF_NORMALVERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_NORMAL) //flexible vertex format
#define FVF_VERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1) //flexible vertex format




class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual void SetMapAndTexture(std::string heightMapFileName, std::string _textureName);

	virtual bool InitWithTexture(Renderer*);	//
	virtual void Invalidate();



	virtual void SetupMatrices(Renderer*);
	//virtual bool InitWithColor(Renderer*);
	virtual void Draw(Renderer*);

	Transform transform;
private:

	virtual void CleanUp();
	virtual bool LoadBMP(std::string);

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
