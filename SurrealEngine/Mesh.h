/*! \file  Mesh.h
\brief this is class is a combination of vertices and textures to create a model from a .x file
*/



#ifndef MESH_H_
#define MESH_H_

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <string>
#include "Renderer.h"
#include <comdef.h>

#include "Resource.h"

class Mesh: public Resource						//! inherits from resource
{
public:
	Mesh(std::string);							//! needs a name with which it can be indentified as a mesh
	virtual ~Mesh();

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
#endif // !MESH_H_