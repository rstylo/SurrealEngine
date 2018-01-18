#include "Terrain.h"

struct xyzTextureVertex
{
	//! terrain vertex with position, texture, diffuse color and normal.
	D3DXVECTOR3 position;
	FLOAT tu, tv;

	DWORD color;        // kleur
	D3DXVECTOR3 normal;
	
	xyzTextureVertex() {};
	xyzTextureVertex(float _x, float _y, float _z, FLOAT _u, FLOAT _v, DWORD _color) {
		position.x = _x;
		position.y = _y;
		position.z = _z;
		tu = _u;
		tv = _v;
		color = _color;
		normal = position;
	}

};

Terrain::Terrain()
	:primCount(0), vertexCount(0)
{
	//! initialises with transform position and rotation all set to origin point
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
	//! sets terrains heightmap and texturename, and readies initialiazation before next draw routine
	heightMapFileName = _heightMapFileName;
	textureName = _textureName;
	initialized = false;
}

void Terrain::Invalidate()
{
	//! reales vertex and index buffers + texture to free space
	initialized = false;
	CleanUp();
}

void Terrain::SetupMatrices(Renderer* renderer, Transform origin)
{
	transform.SetupMatrices(renderer, origin);
}

bool Terrain::Init(Renderer* renderer)
{
	//! initialises with one vertice *width*lenght of a given heightmap with a texture
	//! no normals or color included!!

	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();
		CleanUp();

		//y waarde ophalen uit de heightmap
		if (!LoadBMP(heightMapFileName.c_str()))
		{
			MessageBox(NULL, "failed loading heightmap", NULL, NULL);
			initialized = false;
			return false;

		}
		printf("succesfully loaded the heightmap... \n");


		//! Creates terrain with
		const int numOfVertices = width * depth;						//! -1 vertices per quad
		const int numOfIndices = width * depth * 6;						//! -6 indicies per quad

		primCount = width * depth * 2;										//! -2 triangles per quad
		vertexCount = numOfVertices;

		xyzTextureVertex* vertices = new xyzTextureVertex[numOfVertices];	//! - vertex array
		WORD* indicies = new WORD[numOfIndices];							//! - index array

		int sizeOfVertices = numOfVertices * sizeof(xyzTextureVertex);		//! - sizeof the vertex array
		int sizeOfIndices = numOfIndices * sizeof(WORD);					//! - sizeof the indexarray

		int vCounter = 0;													//! - current index for inserting vertices
		int iCounter = 0;													//! - current index for inserting vertex-indecis

		D3DXVECTOR2 textureCords;											//! - texture coordinates (u,v)
		textureCords.x = 0;
		textureCords.y = 0;

		float uScale = 4 / width;											//! - texture scale
		float vScale = 4 / depth;


		//! Iterate though x and z
		for (int x = 0; x < width; x++)
		{

			for (int z = 0; z < depth; z++)
			{
				//! - gets height for currentpoint from heightmap
				float height0 = (float)heightData[x * depth + z]; //! inline stament to check if outofbound


				//! - decides point for the to be drawn quad
				int p2 = vCounter;

				int p1 = (vCounter >= depth) ? vCounter - depth : p2;
				
				int p4 = (z + 1 < depth) ? vCounter + 1 : p2;

				int p3 = (z + 1 < depth && vCounter + 1 >= depth) ? vCounter + 1 - depth : p1;

				// - inserts index of vertex-array to create two triangles
				indicies[iCounter]     = p2;
				indicies[iCounter + 1] = p1;
				indicies[iCounter + 2] = p4;


				indicies[iCounter + 3] = p4;
				indicies[iCounter + 4]  = p1;
				indicies[iCounter + 5]  = p3;
				

				iCounter += 6;



				//! - creates current vertice on point x,z and inserts height data.
				vertices[vCounter] = { 0.0f + x, height0, 0.0f + z, textureCords.x, textureCords.y, 0x00800000 };
				vCounter++;

				if (textureCords.y > 0)
					textureCords.y = 0;
				else
					textureCords.y = 1;
			}

			if (textureCords.x > 0)
				textureCords.x = 0;
			else
				textureCords.x = 1;

			textureCords.y = 0;
		}



		// create the to be drawn vertex buffer
		if (!SUCCEEDED(device->CreateVertexBuffer(sizeOfVertices,
			0, FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE,
			D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
		{
			printf("failed creating vertex buffer... \n");
			initialized = false;
			return false;
		}

		// create the index buffer for the to be drawn vertices
		if (!SUCCEEDED(device->CreateIndexBuffer(sizeOfIndices,
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
			D3DPOOL_MANAGED, &indexBuffer, NULL)))
		{
			printf("failed creating index buffer... \n");
			initialized = false;
			return false;
		}

		// insert the vertices into the to be drawn vertexbuffer
		VOID* pVertices;
		if (!SUCCEEDED(vertexBuffer->Lock(0, sizeOfVertices, (void**)&pVertices, 0)))
		{
			printf("failed filling the vertex buffer... \n");
			initialized = false;
			return false;
		}
		memcpy(pVertices, vertices, sizeOfVertices);
		vertexBuffer->Unlock();


		// insert the indecis into the to be drawn indexbuffer
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

		//! gets the texture
		D3DXCreateTextureFromFile(device, textureName.c_str(), &texture);
		if (!texture)
		{
			MessageBox(NULL, "failed initialising texture", NULL, NULL);
			initialized = false;
			return false;
		}

		//! returns true is succesful
		initialized = true;
		return true;
	}
}

void Terrain::Draw(Renderer* renderer)
{
	//! draws the terrain if initialised
	if (initialized == false)
	{
		Init(renderer);
	}
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();
		if (vertexBuffer != NULL && indexBuffer != NULL && texture != NULL)
		{
			device->SetTexture(0, texture);

			//device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	//only if renderstate light is true
			device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);	

			device->SetStreamSource(0, vertexBuffer, 0, sizeof(xyzTextureVertex));
			device->SetIndices(indexBuffer);
			device->SetFVF(FVF_TEXTUREDVERTEX_STRUCTURE);

		

			device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, primCount);
		}
	}
}



void Terrain::CleanUp()
{
	//! releases vertexbuffer and indexbuffer + texture
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

bool Terrain::LoadBMP(std::string argFileName)
{
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

std::string Terrain::GetMapFileName()
{
	return heightMapFileName;
}

std::string Terrain::GetTextureName()
{
	return textureName;
}

byte* Terrain::getHeightArray()
{
	return heightData;
}

int Terrain::getTerrainWidth()
{
	return width;
}

int Terrain::getTerrainDepth()
{
	return depth;
}

bool Terrain::getInitialized()
{
	return initialized;
}