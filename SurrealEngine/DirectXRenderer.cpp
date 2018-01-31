#include "DirectXRenderer.h"
#include "logger.h"



DirectXRenderer::DirectXRenderer()
{
	logger.Logtime();
	dxManager = new DxManager();
}


DirectXRenderer::~DirectXRenderer()
{
	//! releases directx and its device to free space
	if (device != NULL)
	{
		device->Release();					
		device = NULL;
	}

	if (direct3d != NULL)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}

bool DirectXRenderer::Init(HWND hWnd, bool windowed)
{
	//! Initialise directx and its rendering device with a window in windowed or not.


	//drd pointer met variablen
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);  //D3D9b_SDK_VERSION??

	//belangrijkje params voor d3d deviice
	D3DPRESENT_PARAMETERS presParams;				//"presentation" parameters
	ZeroMemory(&presParams, sizeof(presParams));

	presParams.hDeviceWindow = hWnd;
	presParams.Windowed = windowed;
	presParams.BackBufferCount = 1;
	presParams.BackBufferFormat = D3DFMT_UNKNOWN;
	presParams.MultiSampleType = D3DMULTISAMPLE_NONE;		// "anti ailising"
	presParams.MultiSampleQuality = 0;

	presParams.SwapEffect = D3DSWAPEFFECT_COPY;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.AutoDepthStencilFormat = D3DFMT_D16;

	//presParams.Flags = 0;
	//presParams.EnableAutoDepthStencil = true;
	//presParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	//presParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//presParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;	//snelste mogelijkheid, geen overhead die wel hebt bij andere swapeffecten zie msdn

	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &device))) //mixed vortex = gecompineerd hardware n software 3d berekeningen
	{
		MessageBox(NULL, "issue creating gfx device", NULL, NULL);
		logger.Log("issue creating gfx device", "Error");
		return false;
	}

	// Turn off culling, so we see the front and back of the triangle
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//drawn on D3DCULL_CCW

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// Turn off D3D lighting, since we are providing our own vertex colors
	device->LightEnable(0, TRUE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_AMBIENT, 0x008D6056);


	return true;


}

void DirectXRenderer::Clear(D3DCOLOR color)
{
	//! clear the back buffer and zbuffer with a color for the background
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);	//backbuffer clear 
}

bool DirectXRenderer::Begin() {
	//! start the drawing process for a frame, returns false when unsuccesful

	if (SUCCEEDED(device->BeginScene()))
	{
		return true;
	}
	return false;
}

void DirectXRenderer::End() {
	//! Ends the frame

	device->EndScene();
}

void DirectXRenderer::Present(HWND wnd) {
	//! presents the created frame to the screen
	device->Present(NULL, NULL, wnd, NULL);
}

LPDIRECT3DDEVICE9* DirectXRenderer::GetDevice()
{
	//! get rendering device
	return &device;
}

void DirectXRenderer::Log(std::string text, std::string type)
{
	logger.Log(text, type);
}

void DirectXRenderer::Flush()
{
	logger.Flush();
}

void DirectXRenderer::SetupMatrices(Vector3 position, Vector3 rotation)
{

	D3DXMATRIX worldMtrx;
	D3DXMatrixIdentity(&worldMtrx);

	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);

	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;

	D3DXMatrixRotationX(&rotX, rotation.x);
	D3DXMatrixRotationY(&rotY, rotation.y);
	D3DXMatrixRotationZ(&rotZ, rotation.z);

	worldMtrx = trans* rotZ * rotY * rotX;

	device->SetTransform(D3DTS_WORLD, &worldMtrx);
}

void DirectXRenderer::SetupMatrices(Vector3 position, Vector3 rotation, Vector3 position2, Vector3 rotation2)
{
	Vector3 tempposition = position2;
	D3DXMATRIX cameraMtrx, worldMtrx;

	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, tempposition.x, tempposition.y, tempposition.z);

	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;

	Vector3 temprotation = rotation2;

	D3DXMatrixRotationX(&rotX, temprotation.x);
	D3DXMatrixRotationY(&rotY, temprotation.y);
	D3DXMatrixRotationZ(&rotZ, temprotation.z);


	cameraMtrx = trans* rotZ * rotY * rotX;

	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
	D3DXMatrixRotationX(&rotX, rotation.x);
	D3DXMatrixRotationY(&rotY, rotation.y);
	D3DXMatrixRotationZ(&rotZ, rotation.z);

	worldMtrx = rotX*rotY*rotZ*trans;
	worldMtrx *= cameraMtrx;

	device->SetTransform(D3DTS_WORLD, &worldMtrx);
}

void DirectXRenderer::SetupMatricesRotate(Vector3 _rotation)
{

	D3DXMATRIX worldMtrx;
	D3DXMatrixIdentity(&worldMtrx);

	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;

	D3DXMatrixRotationX(&rotX, _rotation.x);
	D3DXMatrixRotationY(&rotY, _rotation.y);
	D3DXMatrixRotationZ(&rotZ, _rotation.z);

	worldMtrx = rotZ * rotY * rotX;

	device->SetTransform(D3DTS_WORLD, &worldMtrx);
}




bool DirectXRenderer::LoadHeightMapWithBmp(std::string heightMapName)
{
	DxHeightMap* dxHeightMap;
	if (dxManager->GetHeightMap(heightMapName) == NULL)
	{
		dxHeightMap = new DxHeightMap();
		dxHeightMap->heightMapName = heightMapName;
		dxManager->AddHeightMap(dxHeightMap);
	}


	dxHeightMap = dxManager->GetHeightMap(heightMapName);

	//! load height map from give path and inserts into heightmap data
	//! is called on program initialization
	HDC deviceContext;
	HANDLE bmp;
	HINSTANCE hInstance = NULL;


	deviceContext = CreateCompatibleDC(NULL);
	if (deviceContext == NULL)
	{
		DeleteDC(deviceContext);
		return false;
	}

	bmp = LoadImage(hInstance, heightMapName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bmp == NULL)
	{
		bmp = LoadImage(hInstance, ("..\\" + heightMapName).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bmp == NULL) {
			char s[100];
			wsprintf(s, "Can't find HeightMask %s", heightMapName);
			MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
			return false;
		}
	}

	SelectObject(deviceContext, bmp);

	BITMAP bitmap;

	GetObject(bmp, sizeof(BITMAP), (void*)&bitmap);

	dxHeightMap->width = bitmap.bmWidth;
	dxHeightMap->depth = bitmap.bmHeight;

	dxHeightMap->heightData = new BYTE[dxHeightMap->width * dxHeightMap->depth];

	for (int itW = 0; itW < dxHeightMap->width; itW++)
	{
		for (int itH = 0; itH < dxHeightMap->depth; itH++)
		{
			dxHeightMap->heightData[itW * dxHeightMap->depth + itH] = GetRValue(GetPixel(deviceContext, itW, itH));
		}
	}
	return true;



		

}

byte * DirectXRenderer::GetHeightData(std::string heightMapName)
{
	DxHeightMap* dxHeightMap = dxManager->GetHeightMap(heightMapName);
	if (dxHeightMap != NULL)
	{
		return dxHeightMap->heightData;
	}

	return NULL;
}

int DirectXRenderer::GetHeightMapWidth(std::string heightMapName)
{
	DxHeightMap* dxHeightMap = dxManager->GetHeightMap(heightMapName);
	if (dxHeightMap != NULL)
	{
		return dxHeightMap->width;
	}

	return 0;
}

int DirectXRenderer::GetHeightMapDepth(std::string heightMapName)
{
	DxHeightMap* dxHeightMap = dxManager->GetHeightMap(heightMapName);
	if (dxHeightMap != NULL)
	{
		return dxHeightMap->depth;
	}

	return 0;
}

int DirectXRenderer::UnLoadHeightMap(std::string heightMapName)
{
	dxManager->DeleteHeightMap(heightMapName);
	return 0;
}

bool DirectXRenderer::LoadMesh(std::string meshName)
{
	
	DxMesh* dxMesh;

	if (dxManager->GetMesh(meshName) == NULL)	//! create a new mesh
	{
		dxMesh = new DxMesh();
		dxMesh->meshPath = meshName;
		dxManager->AddMesh(dxMesh);
	}

	dxMesh = dxManager->GetMesh(meshName);

	//! intialise the mesh, returns if creation is succeful using a texture and a model
		if (dxMesh->initialized == false)
		{
			

			LPD3DXBUFFER materialBuffer;



			if (!SUCCEEDED(D3DXLoadMeshFromX((dxMesh->meshPath).c_str(), D3DXMESH_SYSTEMMEM,
				device, NULL,
				&materialBuffer, NULL, &(dxMesh->numOfMaterials),
				&(dxMesh->mesh))))
			{
				if (!SUCCEEDED(D3DXLoadMeshFromX(("..\\" + (dxMesh->meshPath)).c_str(), D3DXMESH_SYSTEMMEM,
					device, NULL,
					&materialBuffer, NULL, &(dxMesh->numOfMaterials),
					&(dxMesh->mesh))))
				{
					MessageBox(NULL, (std::string("Could not find " + dxMesh->meshPath)).c_str(), NULL, NULL);
					Log("Could not find " + dxMesh->meshPath, "Error");
					dxManager->DeleteMesh(meshName);
					return false;
				}
			}


			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
			dxMesh->materials = new D3DMATERIAL9[dxMesh->numOfMaterials];


			if (dxMesh->materials == NULL)
			{
				return false;
			}
			dxMesh->textures = new LPDIRECT3DTEXTURE9[dxMesh->numOfMaterials];
			if (dxMesh->textures == NULL)
			{
				dxManager->DeleteMesh(meshName);
				return false;
			}

			for (DWORD i = 0; i < dxMesh->numOfMaterials; i++)
			{
				// Copy the material
				dxMesh->materials[i] = d3dxMaterials[i].MatD3D;

				// Set the ambient color for the material (D3DX does not do this)
				dxMesh->materials[i].Ambient = dxMesh->materials[i].Diffuse;

				dxMesh->textures[i] = NULL;
				if (d3dxMaterials[i].pTextureFilename != NULL &&
					lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
				{
					// Create the texture
					if (!SUCCEEDED((D3DXCreateTextureFromFileA(device,
						d3dxMaterials[i].pTextureFilename,
						&(dxMesh->textures[i])))))
					{
						// If texture is not in current folder, try parent folder
						const CHAR* strPrefix = "..\\";
						CHAR strTexture[MAX_PATH];
						strcpy_s(strTexture, MAX_PATH, strPrefix);
						strcat_s(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
						// If texture is not in current folder, try parent folder
						if (!SUCCEEDED((D3DXCreateTextureFromFileA(device,
							strTexture,
							&(dxMesh->textures[i])))))
						{
							MessageBox(NULL, "Could not find texture map", NULL, NULL);
							Log("Could not find texture map", "Error");
						}
					}
				}
			}

			// Done with the material buffer
			materialBuffer->Release();
			dxMesh->initialized = true;
			return true;
		}
		return false;
}

void DirectXRenderer::DrawMesh(std::string meshName)
{
	DxMesh* dxMesh = dxManager->GetMesh(meshName);

	if (dxMesh != NULL && dxMesh->textures && dxMesh->materials && dxMesh->initialized)
	{
		for (DWORD i = 0; i < dxMesh->numOfMaterials; i++)
		{
			device->SetMaterial(&(dxMesh->materials[i]));
			device->SetTexture(0, dxMesh->textures[i]);

			dxMesh->mesh->DrawSubset(i);
		}
	}
}

void DirectXRenderer::UnLoadMesh(std::string meshName)
{
	dxManager->DeleteMesh(meshName);
}

bool DirectXRenderer::LoadTexture(std::string textureName)
{

	DxTexture* dxTexture;

	if (dxManager->GetTexture(textureName) == NULL)	//! create a new texture
	{

		dxTexture = new DxTexture();
		dxTexture->textureName = textureName;
		dxManager->AddTexture(dxTexture);
	}

	dxTexture = dxManager->GetTexture(textureName);


	D3DXCreateTextureFromFile(device, dxTexture->textureName.c_str(), &(dxTexture->texture));
	if (!dxTexture->texture)
	{
		D3DXCreateTextureFromFile(device, ("..\\" + dxTexture->textureName).c_str(), &(dxTexture->texture));
		if (!dxTexture->texture) {
			MessageBox(NULL, std::string("failed initialising texture: " + dxTexture->textureName).c_str(), NULL, NULL);
			return false;
		}
		return true;
	}

	return true;
}

void DirectXRenderer::DrawTexture(std::string textureName)
{
	DxTexture* dxTexture = dxManager->GetTexture(textureName);
	
	if (dxTexture != NULL && dxTexture->texture)
	{
		device->SetTexture(0, dxTexture->texture);

		//device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	//only if renderstate light is true
		device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	}
}

void DirectXRenderer::UnLoadTexture(std::string textureName)
{
	dxManager->DeleteTexture(textureName);
}

void DirectXRenderer::GetTextureDesc(std::string textureName, D3DSURFACE_DESC* value)
{
	DxTexture* dxTexture = dxManager->GetTexture(textureName);

	if (dxTexture != NULL && dxTexture->texture)
	{
		dxTexture->texture->GetLevelDesc(0, value);
	}

}

bool DirectXRenderer::LoadIndexedVertices(std::string name, int _primCount, int _vertexCount, xyzTextureVertex * vertices, WORD * indices, int sizeOfVertices, int sizeOfIndices)
{
	DxVertexBuffer* dxVertexBuffer;

	if (dxManager->GetVertexBuffer(name) == NULL)	//! create a new texture
	{
		dxVertexBuffer = new DxVertexBuffer();
		dxVertexBuffer->name = name;
		dxManager->AddVertexBuffer(dxVertexBuffer);
	}

	dxVertexBuffer = dxManager->GetVertexBuffer(name);


	dxVertexBuffer->primCount = _primCount;
	dxVertexBuffer->vertexCount = _vertexCount;

	// create the to be drawn vertex buffer
	if (!SUCCEEDED(device->CreateVertexBuffer(sizeOfVertices,
		0, FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE,
		D3DPOOL_DEFAULT, &(dxVertexBuffer->vertexBuffer), NULL)))
	{
		printf("failed creating vertex buffer... \n");
		return false;
	}

	// create the index buffer for the to be drawn vertices
	if (!SUCCEEDED(device->CreateIndexBuffer(sizeOfIndices,
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &(dxVertexBuffer->indexBuffer), NULL)))
	{
		printf("failed creating index buffer... \n");
		return false;
	}

	// insert the vertices into the to be drawn vertexbuffer
	VOID* pVertices;
	if (!SUCCEEDED(dxVertexBuffer->vertexBuffer->Lock(0, sizeOfVertices, (void**)&pVertices, 0)))
	{
		printf("failed filling the vertex buffer... \n");
		return false;
	}
	memcpy(pVertices, vertices, sizeOfVertices);
	dxVertexBuffer->vertexBuffer->Unlock();


	// insert the indecis into the to be drawn indexbuffer
	VOID* pIndices;
	if (!SUCCEEDED(dxVertexBuffer->indexBuffer->Lock(0, sizeOfIndices, (void**)&pIndices, 0)))
	{
		printf("failed filling the index buffer... \n");
		return false;
	}
	memcpy(pIndices, indices, sizeOfIndices);
	dxVertexBuffer->indexBuffer->Unlock();

	return true;
}

void DirectXRenderer::DrawVertices(std::string name)
{
	DxVertexBuffer* dxVertexBuffer = dxManager->GetVertexBuffer(name);

	if (dxVertexBuffer != NULL && device != NULL && dxVertexBuffer->vertexBuffer != NULL && dxVertexBuffer->indexBuffer != NULL)
	{
		device->SetStreamSource(0, dxVertexBuffer->vertexBuffer, 0, sizeof(xyzTextureVertex));
		device->SetIndices(dxVertexBuffer->indexBuffer);
		device->SetFVF(FVF_TEXTUREDVERTEX_STRUCTURE);



		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, dxVertexBuffer->vertexCount, 0, dxVertexBuffer->primCount);
	}
}

void DirectXRenderer::DrawVerticesBackground(std::string name)
{
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	DrawVertices(name);

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void DirectXRenderer::UnLoadVertices(std::string name)
{
	dxManager->DeleteVertexBuffer(name);
}

