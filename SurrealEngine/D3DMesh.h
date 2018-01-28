#ifndef D3DMESH_H_
#define D3DMESH_H_

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <string>
#include "Renderer.h"
#include <comdef.h>

class D3DMesh
{
public:
	D3DMesh(std::string);							//! needs a name with which it can be indentified as a mesh
	virtual ~D3DMesh();

	virtual bool Init(Renderer*);
	virtual void Draw(Renderer*);

	virtual std::string GetMeshName();
	virtual void CleanUp();


private:

	LPD3DXMESH          mesh = NULL;			//! Our mesh object in sysmem
	D3DMATERIAL9*       materials = NULL;		//! Materials for our mesh
	LPDIRECT3DTEXTURE9* textures = NULL;		//! Textures for our mesh
	DWORD               numOfMaterials = 0L;	//! Number of mesh materials

	std::string meshPath;						//! mesh identifier and file location
	bool initialized;
};

#endif	// !D3DMESH_H_