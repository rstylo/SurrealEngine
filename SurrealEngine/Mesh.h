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
	LPDIRECT3DDEVICE9   device;
	LPD3DXMESH          mesh; // Our mesh object in sysmem
	D3DMATERIAL9*       meshMaterials; // Materials for our mesh
	DWORD               dwNumMaterials;   // Number of mesh materials

};

#endif // !MESH_H_
