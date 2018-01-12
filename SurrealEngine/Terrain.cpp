#include "Terrain.h"

struct xyzColorVertex
{
	FLOAT x, y, z;      // 3d positie
	DWORD color;        // kleur
};

struct xyzTextureVertex
{
	FLOAT x, y, z, u, v;      // 3d positie en texture u v
	D3DXVECTOR3 normal;
	xyzTextureVertex() {};
	xyzTextureVertex(float _x, float _y, float _z, float _u, float _v) {
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	}
};

Terrain::Terrain()
	:primCount(0), vertexCount(0)
{
	transform.SetPosition(Vector3(0, 0, 0));
	transform.SetRotation(Vector3(0, 0, 0));

	initialized = false;
}

Terrain::~Terrain()
{
	CleanUp();
}

void Terrain::SetMapAndTexture(std::string _heightMapFileName, std::string _textureName)
{
	heightMapFileName = _heightMapFileName;
	textureName = _textureName;
	initialized = false;
}

void Terrain::Invalidate()
{
	initialized = false;
	CleanUp();
}

bool Terrain::InitWithTexture(LPDIRECT3DDEVICE9 device)
{

	CleanUp();

	//y waarde ophalen uit de heightmap
	if (!LoadBMP(heightMapFileName.c_str()) )
	{
		MessageBox(NULL, "failed loading heightmap", NULL, NULL);
		initialized = false;
		return false;

	}
	printf("succesfully loaded the heightmap... \n");


	//constante varibablen declarenen voor grote van de array
     const int numOfVertices = width * depth * 4;						//4 vertices per quad
	 const int numOfIndices = width * depth * 6;						//6 indicies per quad

	primCount = width * depth * 2;										//2 triangles per quad
	vertexCount = numOfVertices;					

	xyzTextureVertex* vertices = new xyzTextureVertex[numOfVertices];	//vertex array
	 WORD* indicies = new WORD[numOfIndices];							//vertex-index array

	int sizeOfVertices = numOfVertices * sizeof(xyzTextureVertex);		//sizeof the vertex array
	int sizeOfIndices = numOfIndices * sizeof(WORD);					//sizeof the indexarray

	int vCounter = 0;													//current index for inserting vertices
	int iCounter = 0;													//current index for inserting vertex-indecis

	int halfX = width / 2;												
	int halfZ = depth / 2;												


	//iterate though x and y
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			//index nmr naar vertex om twee driehoeken te vormen
			indicies[iCounter] = 0 + vCounter;
			indicies[iCounter + 1] = 1 + vCounter;
			indicies[iCounter + 2] = 2 + vCounter;
			indicies[iCounter + 3] = 2 + vCounter;
			indicies[iCounter + 4] = 1 + vCounter;
			indicies[iCounter + 5] = 3 + vCounter;
			iCounter += 6;

			//vertices (punten/hoeken) van een quad
			vertices[vCounter + 0] = { 0.0f + x - halfX, (float)heightData[x * depth + z],														0.0f + z - halfZ, 0.0f, 0.0f };	//inline stament to check if outofbound, last to decide the u and v its texture
			vertices[vCounter + 0].normal = D3DXVECTOR3(0.0f + x - halfX, (float)heightData[x * depth + z], 0.0f + z - halfZ);

			vertices[vCounter + 1] = { 1.0f + x - halfX, (float)heightData[(x + 1 >= width? x : x+1) * depth + z],								0.0f + z - halfZ, 1.0f, 0.0f };
			vertices[vCounter + 1].normal = D3DXVECTOR3(1.0f + x - halfX, (float)heightData[(x + 1 >= width ? x : x + 1) * depth + z], 0.0f + z - halfZ);

			vertices[vCounter + 2] = { 0.0f + x - halfX, (float)heightData[x * depth + (z + 1 >= depth ? z : z + 1)],							1.0f + z - halfZ, 0.0f, 1.0f };
			vertices[vCounter + 2].normal = D3DXVECTOR3(0.0f + x - halfX, (float)heightData[x * depth + (z + 1 >= depth ? z : z + 1)], 1.0f + z - halfZ);

			vertices[vCounter + 3] = { 1.0f + x - halfX, (float)heightData[(x + 1 >= width? x : x+1) * depth + (z + 1 >= depth ? z : z+1)]	,	1.0f + z - halfZ, 1.0f, 1.0f };
			vertices[vCounter + 3].normal = D3DXVECTOR3(1.0f + x - halfX, (float)heightData[(x + 1 >= width ? x : x + 1) * depth + (z + 1 >= depth ? z : z + 1)], 1.0f + z - halfZ);
			vCounter += 4;
		}
	}

	

	//create the to be drawn vertex buffer
	if (!SUCCEEDED(device->CreateVertexBuffer(sizeOfVertices,
		0, FVF_NORMALVERTEX_TEXTURESTRUCTURE,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		printf("failed creating vertex buffer... \n");
		initialized = false;
		return false;
	}

	//create the index buffer for the to be drawn vertices
	if (!SUCCEEDED(device->CreateIndexBuffer(sizeOfIndices,
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &indexBuffer, NULL)))
	{
		printf("failed creating index buffer... \n");
		initialized = false;
		return false;
	}

	//insert the vertices into the to be drawn vertexbuffer
	VOID* pVertices;
	if (!SUCCEEDED(vertexBuffer->Lock(0, sizeOfVertices, (void**)&pVertices, 0)))
	{
		printf("failed filling the vertex buffer... \n");
		initialized = false;
		return false;
	}
	memcpy(pVertices, vertices, sizeOfVertices);
	vertexBuffer->Unlock();


	//insert the indecis into the to be drawn indexbuffer
	VOID* pIndicies;
	if (!SUCCEEDED(indexBuffer->Lock(0, sizeOfIndices, (void**)&pIndicies, 0)))
	{
		printf("failed filling the index buffer... \n");
		initialized = false;
		return false;
	}
	memcpy(pIndicies, indicies, sizeOfIndices);
	indexBuffer->Unlock();

	printf("Terrain vertexbuffers succefully created...\n");
	
	//get the texture
	D3DXCreateTextureFromFile(device, textureName.c_str(), &texture);
	if (!texture)
	{
		MessageBox(NULL, "failed initialising texture", NULL, NULL);
		initialized = false;
		return false;
	}

	initialized = true;
	return true;
}



void Terrain::Draw(LPDIRECT3DDEVICE9 device)
{
	if (initialized == false)
	{
		InitWithTexture(device);
	}
	if (vertexBuffer != NULL && indexBuffer != NULL && texture != NULL) 
		{
			device->SetTexture(0, texture);
			device->SetStreamSource(0, vertexBuffer, 0, sizeof(xyzTextureVertex));
			device->SetIndices(indexBuffer);
			device->SetFVF(FVF_NORMALVERTEX_TEXTURESTRUCTURE);

			device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, primCount);
		}
}



void Terrain::CleanUp()
{

	if (vertexBuffer != NULL)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}

	if (indexBuffer != NULL)
	{
		indexBuffer->Release();
		indexBuffer = NULL;
	}

	if (texture != NULL)
	{
		texture->Release();
		texture = NULL;
	}

	if (heightData != NULL)
	{
		delete heightData;
		heightData = NULL;
	}
}

void Terrain::SetupMatrices(LPDIRECT3DDEVICE9 device)
{
	transform.SetupMatrices(device);
}

bool Terrain::LoadBMP(std::string argFileName)
{

	HDC deviceContext;										
	HANDLE bmp;									
	HINSTANCE hInstance = NULL;					

						   
	deviceContext = CreateCompatibleDC(NULL);		
	if (deviceContext == NULL)
	{
		DeleteDC(deviceContext);													
		return false;																		
	}

	bmp = LoadImage(hInstance, argFileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bmp == NULL)	
	{
		char s[100];
		wsprintf(s, "Can't find HeightMask %s", argFileName);
		MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
		return false;		
	}

	SelectObject(deviceContext, bmp);

	BITMAP bitmap;

	GetObject(bmp, sizeof(BITMAP), (void*)&bitmap);

	width = bitmap.bmWidth;
	depth = bitmap.bmHeight;

	heightData = new BYTE[width * depth];

	for (int itW = 0; itW < width; itW++)
	{
		for (int itH = 0; itH < depth; itH++)
		{
			heightData[itW * depth + itH] = GetRValue(GetPixel(deviceContext, itW, itH));
		}
	}
	return true;
}