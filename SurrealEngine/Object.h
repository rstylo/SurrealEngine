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

	virtual bool Init(LPDIRECT3DDEVICE9, float, float, float, float);
	virtual void Draw(LPDIRECT3DDEVICE9);
	
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	//LPDIRECT3DTEXTURE9 texture;

	//D3DXVECTOR3 position;
	//D3DXVECTOR3 rotation;
	//D3DXVECTOR3 scale;
	

private:
	struct ObjectVertex
	{
		FLOAT x, y, z;      // 3d positie
		DWORD color;        // kleur
	};
};

#endif // !OBJECT_H_