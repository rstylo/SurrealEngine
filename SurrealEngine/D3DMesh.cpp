#include "D3DMesh.h"
#include "DirectXRenderer.h"


D3DMesh::D3DMesh(std::string _meshPath)
{
	meshPath = _meshPath;
}

D3DMesh::~D3DMesh()
{
}

bool D3DMesh::Init(Renderer *renderer)
{
	//! intialise the mesh, returns if creation is succeful using a texture and a model
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();


		if (initialized == false)
		{
			CleanUp();
			LPD3DXBUFFER materialBuffer;

			if ( !SUCCEEDED(D3DXLoadMeshFromX(meshPath.c_str(), D3DXMESH_SYSTEMMEM,
				device, NULL,
				&materialBuffer, NULL, &numOfMaterials,
				&mesh)))
			{
				if (!SUCCEEDED(D3DXLoadMeshFromX(("..\\" + meshPath).c_str(), D3DXMESH_SYSTEMMEM,
					device, NULL,
					&materialBuffer, NULL, &numOfMaterials,
					&mesh)))
				{
					MessageBox(NULL, (std::string("Could not find " + meshPath)).c_str(), NULL, NULL);
					renderer->Log("Could not find " + meshPath, "Error");
					CleanUp();
					return false;
				}
			}


			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
			materials = new D3DMATERIAL9[numOfMaterials];


			if (materials == NULL)
			{
				return false;
			}
			textures = new LPDIRECT3DTEXTURE9[numOfMaterials];
			if (textures == NULL)
			{
				CleanUp();
				return false;
			}

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
							renderer->Log("Could not find texture map", "Error");
						}
					}
				}
			}

			// Done with the material buffer
			materialBuffer->Release();
			initialized = true;
		}
		return true;
	}
	return false;
}

void D3DMesh::Draw(Renderer *renderer)
{
	//! draw the mesh if already inialised
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();
		if (textures && materials && initialized == true)
		{
			for (DWORD i = 0; i < numOfMaterials; i++)
			{
				device->SetMaterial(&materials[i]);
				device->SetTexture(0, textures[i]);

				mesh->DrawSubset(i);
			}
		}
	}

}

std::string D3DMesh::GetMeshName()
{
	return std::string();
}

void D3DMesh::CleanUp()
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

	initialized = false;
}