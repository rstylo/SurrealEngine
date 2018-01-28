#ifndef D3DVERTEXBUFFER_H_
#define D3DVERTEXBUFFER_H_

#include <d3dx9.h>
#include <iostream>

#include <cmath>

#define FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE|D3DFVF_NORMAL) //! flexible vertex format
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

class D3DVertexBuffer
{
public:
	D3DVertexBuffer();
	virtual ~D3DVertexBuffer();

	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual bool Init(LPDIRECT3DDEVICE9, int, int, xyzTextureVertex *, WORD *, int, int);

	virtual void CleanUp();

private:
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;

	int primCount;
	int vertexCount;


};

#endif //! D3DVERTEXBUFFER_H_

