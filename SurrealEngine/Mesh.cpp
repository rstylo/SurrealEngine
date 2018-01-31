#include "Mesh.h"
#include "DirectXRenderer.h"


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
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
	{
		if (!dxrenderer->LoadMesh(meshName))
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
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->DrawMesh(meshName);
		}
}

std::string Mesh::GetMeshName()
{
	return meshName;
}

void Mesh::CleanUp(Renderer* renderer)
{
	if (renderer != NULL)
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->UnLoadMesh(meshName);
		}
}
