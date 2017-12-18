#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <d3dx9.h>
#include <iostream>
#include <map>
#include <list>

#define FVF_VERTEXSTRUCTURE (D3DFVF_XYZ|D3DFVF_DIFFUSE) //flexible vertex format

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual bool Init(LPDIRECT3DDEVICE9, const int, const int);
	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual bool LoadBMP(char*);

	
private:
	struct xyzColorVertex
	{
		FLOAT x, y, z;      // 3d positie
		DWORD color;        // kleur
	};

	std::list<LPDIRECT3DVERTEXBUFFER9> vertexBuffers;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;				
	LPDIRECT3DINDEXBUFFER9 indexBuffer;


private:
	virtual void CleanUp();
	BYTE* heightData;

	int primCount;
	int vertexCount;
};


#endif // !TERRAIN_H_
