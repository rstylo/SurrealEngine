#include "Mesh.h"
#include <d3dx9.h>

Mesh::Mesh(LPDIRECT3DDEVICE9* _device) : Resource()
{
	device = *_device;
	mesh = NULL;
	dwNumMaterials = NULL;
	meshMaterials = 0L;
}

Mesh::~Mesh()
{

}

void Mesh::Create(std::string name)
{
	if (!SetMesh(name))
	{
		MessageBox(NULL, "Mesh not Loaded", NULL, NULL);
	}
}


boolean Mesh::SetMesh(std::string _fileName)
{

	if (device == NULL)
	{
		MessageBox(NULL, "could not find mesh", NULL, NULL);
	}
	std::string file = "Assets\\" + _fileName;

	LPD3DXBUFFER vertexBuffer; //data buffer, storing vertex

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(file.c_str(), D3DXMESH_SYSTEMMEM, device, NULL, &vertexBuffer, NULL, &dwNumMaterials, &mesh)))
	{
		MessageBox(NULL, "could not find mesh", NULL, NULL);
		return FALSE;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)vertexBuffer->GetBufferPointer();
	meshMaterials = new D3DMATERIAL9[dwNumMaterials];
	if (meshMaterials == NULL)
	{
		MessageBox(NULL, "Mesh is null", NULL, NULL);
		return FALSE;
	}
	
	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		// Copy the material
		meshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
	}

	vertexBuffer->Release();

	return TRUE;
}

void Mesh::Draw()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, 1000.0f);
	device->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	device->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);

	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		
		
		// Set the material and texture for this subset
		device->SetMaterial(&meshMaterials[i]);

		// Draw the mesh subset
		mesh->DrawSubset(i);
	}

	device->EndScene();
}


