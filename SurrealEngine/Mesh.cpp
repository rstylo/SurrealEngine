#include "Mesh.h"
#include "DirectXRenderer.h"
#include "D3DMesh.h"


Mesh::Mesh(std::string _meshPath)
	:Resource()
{
	mesh = new D3DMesh(_meshPath);
}


Mesh::~Mesh()
{
	if (mesh != NULL)
		mesh->CleanUp();
}

bool Mesh::Init(Renderer* renderer)
{
	if(mesh != NULL)
		return mesh->Init(renderer);

	return NULL;
}

void Mesh::Draw(Renderer* renderer)
{
	if(mesh != NULL)
		mesh->Draw(renderer);
}

std::string Mesh::GetMeshName()
{
	if (mesh != NULL)
		return mesh->GetMeshName();

	return "";
}

void Mesh::CleanUp()
{
	if(mesh!=NULL)
		mesh->CleanUp();
}
