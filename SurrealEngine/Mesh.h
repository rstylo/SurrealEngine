#ifndef MESH_H_
#define MESH_H_

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <string>

#include "Resource.h"

class Mesh: public Resource
{
public:
	Mesh(std::string);
	virtual ~Mesh();

	virtual bool Init(LPDIRECT3DDEVICE9);
	virtual void Draw(LPDIRECT3DDEVICE9);

	virtual std::string GetMeshName();
	virtual void CleanUp();
	

private:

	LPD3DXMESH          mesh = NULL; // Our mesh object in sysmem
	D3DMATERIAL9*       materials = NULL; // Materials for our mesh
	LPDIRECT3DTEXTURE9* textures = NULL; // Textures for our mesh
	DWORD               numOfMaterials = 0L;   // Number of mesh materials

	std::string meshPath;
	bool initialized;
};

#endif // !MESH_H_