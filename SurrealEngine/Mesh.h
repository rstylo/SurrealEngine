#ifndef MESH_H_
#define MESH_H_

#include "Resource.h"
#include <d3dx9.h>

class Mesh : public Resource
{
public:
	Mesh(LPDIRECT3DDEVICE9*);
	~Mesh();
	boolean SetMesh(std::string);
	void Draw();
	virtual void Create(std::string);

private:
	LPDIRECT3DDEVICE9   g_pd3dDevice;
	LPD3DXMESH          g_pMesh; // Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials; // Materials for our mesh
	DWORD               g_dwNumMaterials;   // Number of mesh materials

};

#endif // !MESH_H_
