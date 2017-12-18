#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <d3dx9.h>
#include <iostream>
#include <map>
#include <list>
#include <string>

#define FVF_VERTEX_COLORSTRUCTURE (D3DFVF_XYZ|D3DFVF_DIFFUSE) //flexible vertex format
#define FVF_VERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1) //flexible vertex format

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual bool InitWithTexture(LPDIRECT3DDEVICE9, const int, char*, const int, std::string);	//
	//virtual bool InitWithColor(LPDIRECT3DDEVICE9, const int, char*, const int, DWORD, DWORD, DWORD, DWORD);
	virtual void Draw(LPDIRECT3DDEVICE9);

	
private:

	virtual void CleanUp();
	virtual bool LoadBMP(char*);

	std::list<LPDIRECT3DVERTEXBUFFER9> vertexBuffers;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;				
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	
	LPDIRECT3DTEXTURE9 texture;
	
	BYTE* heightData;

	int primCount;
	int vertexCount;
};


#endif // !TERRAIN_H_
