#ifndef OBJECT_H_
#define OBJECT_H_

#include <d3dx9.h>
#include <list>
#include <string>

#define FVF_VERTEXSTRUCTURE (D3DFVF_XYZ|D3DFVF_DIFFUSE) //flexible vertex format

struct ObjectVertex
{
	FLOAT x, y, z;      // 3d positie
	DWORD color;        // kleur
};

class Object
{
public:
	Object(int, int);
	virtual ~Object();

	virtual bool EditObject(LPDIRECT3DDEVICE9, float, float, float, float, float, float) = 0;
	void Draw(LPDIRECT3DDEVICE9);

protected:
	int numVertices;
	int primCount;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
};

#endif // !OBJECT_H_