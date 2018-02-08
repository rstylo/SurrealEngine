/*! \file  Mesh.h
\brief this is class is a combination of vertices and textures to create a model from a .x file
*/


#ifndef MESH_H_
#define MESH_H_

#include <string>
#include "Resource.h"

class D3DMesh;


class Mesh: public Resource					//! inherits from resource
{
public:
	Mesh(std::string);							//! needs a name with which it can be indentified as a mesh
	virtual ~Mesh();	

	virtual bool Init(Renderer*);				//! initialise with a generic renderer
	virtual void Draw(Renderer*);				//! draw mesh with a generic renderer

	virtual std::string GetMeshName();			//! get the meshes name
	virtual void CleanUp(Renderer*);			//! remove this mesh from the renderer
	

private:

	std::string meshName;
};
#endif // !MESH_H_