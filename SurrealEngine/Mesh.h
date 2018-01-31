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

	virtual bool Init(Renderer*);
	virtual void Draw(Renderer*);

	virtual std::string GetMeshName();
	virtual void CleanUp(Renderer*);
	

private:

	std::string meshName;
};
#endif // !MESH_H_