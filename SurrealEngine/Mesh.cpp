#include "Mesh.h"
#include <iostream>
#include <d3dx9.h>

Mesh::Mesh(LPDIRECT3DDEVICE9* _device) : Resource()
{
	g_pd3dDevice = *_device;
}

Mesh::~Mesh()
{

}

void Mesh::Create(std::string _name)
{
	if (!SetMesh(_name))
	{
		MessageBox(NULL, "Mesh not Loaded", NULL, NULL);
	}
}


boolean Mesh::SetMesh(std::string _fileName)
{
	std::string file = "Assets\\" + _fileName;

	std::cout << file.c_str() << std::endl;

	LPD3DXBUFFER pD3DXMtrlBuffer;

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(file.c_str(), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &g_pMesh)))
	{
		MessageBox(NULL, "could not find file", "SurrealEngine", NULL);
		return FALSE;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if (g_pMeshMaterials == NULL)
	{
		MessageBox(NULL, "Mesh is null", "SurrealEngine", NULL);
		return FALSE;
	}
	
	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the material
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

	}

	pD3DXMtrlBuffer->Release();

	return TRUE;
}


void Mesh::Draw()
{
	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Set the material and texture for this subset
		g_pd3dDevice->SetMaterial(&g_pMeshMaterials[i]);

		// Draw the mesh subset
		g_pMesh->DrawSubset(i);
	}
}