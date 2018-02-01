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
	if (renderer != NULL)
	{
		if (!renderer->LoadMesh(meshName))
		{
			renderer->Log("Failed loading mesh", "Error");
			return false;
		}
		return true;
	}
	return false;
}

void Mesh::Draw(Renderer* renderer)
{
	if (renderer != NULL)
		renderer->DrawMesh(meshName);
}

std::string Mesh::GetMeshName()
{
	return meshName;
}

void Mesh::CleanUp(Renderer* renderer)
{
	if (renderer != NULL)
		renderer->UnLoadMesh(meshName);
}
