#ifndef OBJECT_H_
#define OBJECT_H_

#include <d3dx9.h>
#include <map>

#define FVF_VERTEXSTRUCTURE (D3DFVF_XYZ|D3DFVF_DIFFUSE) //flexible vertex format


class Object
{
public:
	Object();
	virtual ~Object();

	virtual bool Init(LPDIRECT3DDEVICE9);
	virtual void Draw(LPDIRECT3DDEVICE9);
	
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9 indexBuffer = NULL;


private:
	struct ObjectVertex
	{
		FLOAT x, y, z;      // 3d positie
		DWORD color;        // kleur
	};

	ObjectVertex  vertices[8];
};

#endif // !OBJECT_H_