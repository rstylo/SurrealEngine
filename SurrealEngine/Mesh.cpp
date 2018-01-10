#include "Mesh.h"



Mesh::Mesh()
	:Resource(), initialized(false)
{
}


Mesh::~Mesh()
{
	if (materials != NULL)
		delete[] materials;

	if (textures)
	{
		for (DWORD i = 0; i < numOfMaterials; i++)
		{
			if (textures[i])
				textures[i]->Release();
		}
		delete[] textures;
	}

	if (mesh != NULL)
	{
		mesh->Release();
		mesh = NULL;
	}
}

bool Mesh::Init(LPDIRECT3DDEVICE9 device)
{
	if (initialized == false)
	{
		LPD3DXBUFFER materialBuffer;

		if (!SUCCEEDED(D3DXLoadMeshFromX("Tiger.x", D3DXMESH_SYSTEMMEM,
			device, NULL,
			&materialBuffer, NULL, &numOfMaterials,
			&mesh)))
		{
			MessageBox(NULL, "Could not find tiger.x", NULL, NULL);
			return false;
		}


		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
		materials = new D3DMATERIAL9[numOfMaterials];
		if (materials == NULL)
			return false;
		textures = new LPDIRECT3DTEXTURE9[numOfMaterials];
		if (textures == NULL)
			return false;

		for (DWORD i = 0; i < numOfMaterials; i++)
		{
			// Copy the material
			materials[i] = d3dxMaterials[i].MatD3D;

			// Set the ambient color for the material (D3DX does not do this)
			materials[i].Ambient = materials[i].Diffuse;

			textures[i] = NULL;
			if (d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
			{
				// Create the texture
				if (!SUCCEEDED((D3DXCreateTextureFromFileA(device,
					d3dxMaterials[i].pTextureFilename,
					&textures[i]))))
				{
					// If texture is not in current folder, try parent folder
					const CHAR* strPrefix = "..\\";
					CHAR strTexture[MAX_PATH];
					strcpy_s(strTexture, MAX_PATH, strPrefix);
					strcat_s(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
					// If texture is not in current folder, try parent folder
					if (!SUCCEEDED((D3DXCreateTextureFromFileA(device,
						strTexture,
						&textures[i]))))
					{
						MessageBox(NULL, "Could not find texture map", NULL, NULL);
					}
				}
			}
		}

		// Done with the material buffer
		materialBuffer->Release();
		initialized = true;



		return true;
	}

	return true;
}

void Mesh::Draw(LPDIRECT3DDEVICE9 device)
{
	


	if (textures && materials)
	{
		for (DWORD i = 0; i < numOfMaterials; i++)
		{

			
			device->SetMaterial(&materials[i]);
			device->SetTexture(0, textures[i]);

			mesh->DrawSubset(i);
		}
	}
}

