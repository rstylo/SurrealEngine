#include "Mesh.h"
#include "Renderer.h"


Mesh::Mesh(std::string _meshPath)
	:Resource()
{
	meshName = _meshPath;
}


Mesh::~Mesh()
{

}

bool Mesh::Init(Renderer* renderer)
{
	// create mesh
	if (renderer != NULL)
	{
		if (!renderer->LoadMesh(meshName))
		{
			return false;
		}
		return true;
	}
	return false;
}

void Mesh::Draw(Renderer* renderer)
{
	// draw mesh
	if (renderer != NULL)
		renderer->DrawMesh(meshName);
}

std::string Mesh::GetMeshName()
{
	return meshName;
}

void Mesh::CleanUp(Renderer* renderer)
{
	// remove mesh from rendering device
	if (renderer != NULL)
		renderer->UnLoadMesh(meshName);
}
