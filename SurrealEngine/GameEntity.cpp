#include <d3dx9.h>
#include "GameEntity.h"
#include <Windows.h>
#include <mmsystem.h>

GameEntity::GameEntity() {}

GameEntity::~GameEntity() {}

void GameEntity::Init(LPDIRECT3DDEVICE9 _g_pd3dDevice)
{
	g_pd3dDevice = _g_pd3dDevice;
	g_pMesh = NULL;
	g_pMeshMaterials = NULL;
	g_pMeshTextures = NULL;
	g_dwNumMaterials = 0L;
	path = "assets\\";
}

HRESULT GameEntity::SetMesh(std::string _fileName)
{
	fileName = path + _fileName;

	LPD3DXBUFFER pD3DXMtrlBuffer;

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(fileName.c_str(), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &g_pMesh)))
	{
		MessageBox(NULL, "could not find file", "SurrealEngine.exe", NULL);
		return E_FAIL;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if (g_pMeshMaterials == NULL)
		return E_OUTOFMEMORY;
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	if (g_pMeshTextures == NULL)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the material
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

		g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			const CHAR* texturePath = "assets\\";
			CHAR strTexture[MAX_PATH];
			strcpy_s(strTexture, MAX_PATH, texturePath);
			strcat_s(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);

			// Create the texture
			if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, strTexture, &g_pMeshTextures[i])))
			{
				MessageBox(NULL, "Could not find texture map", "SurrealEngine.exe", MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();
	return S_OK;
}

void GameEntity::Cleanup()
{
	if (g_pMeshMaterials != NULL)
		delete[] g_pMeshMaterials;
	if (g_pMeshTextures)
	{
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			if (g_pMeshTextures[i])
				g_pMeshTextures[i]->Release();
		}
		delete[] g_pMeshTextures;
	}
	if (g_pMesh != NULL)
		g_pMesh->Release();

}

void GameEntity::Draw()
{
	SetupMatrices();

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Set the material and texture for this subset
		g_pd3dDevice->SetMaterial(&g_pMeshMaterials[i]);
		g_pd3dDevice->SetTexture(0, g_pMeshTextures[i]);

		// Draw the mesh subset
		g_pMesh->DrawSubset(i);
	}
}

// Set up world matrix, copy paste tut06
void GameEntity::SetupMatrices()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, 10.0f);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, 5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
