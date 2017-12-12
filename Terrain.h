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

	virtual bool Init(LPDIRECT3DDEVICE9, const int);
	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual bool LoadBMP(char*);

	
private:
	struct xyzColorVertex
	{
		FLOAT x, y, z;      // 3d positie
		DWORD color;        // kleur
	};

	std::list<LPDIRECT3DVERTEXBUFFER9> vertexBuffers;


private:
	virtual void CleanUp();
	BYTE* heightData;
};

#endif // !TERRAIN_H_
