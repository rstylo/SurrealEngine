#include "Terrain.h"

struct xyzColorVertex
{
	FLOAT x, y, z;      // 3d positie
	DWORD color;        // kleur
};

struct xyzTextureVertex
{
	FLOAT x, y, z, u, v;      // 3d positie en texture u v
	xyzTextureVertex() {};
	xyzTextureVertex(float _x, float _y, float _z, float _u, float _v) {
		x = _x;
		y = _y;
		z = _z;
		u = _u;
		v = _v;
	};
};

Terrain::Terrain()
	:primCount(0), vertexCount(0)
{
	
}

Terrain::~Terrain()
{
	CleanUp();
}

bool Terrain::InitWithTexture(LPDIRECT3DDEVICE9 device, const int width, char* heightMapFileName, const int depth, std::string _textureName)
{
	//y waarde ophalen uit de heightmap
	if (!LoadBMP(heightMapFileName))
	{
		MessageBox(NULL, "failed loading heightmap", NULL, NULL);
		return false;

	}
	printf("succesfully loaded the heightmap... \n");


	//constante varibablen declarenen voor grote van de array
     const int numOfVertices = width * depth * 4;						//4 vertices per quad
	 const int numOfIndices = width * depth * 6;						//6 indicies per quad

	primCount = width * depth * 2;										//2 triangles per quad
	vertexCount = numOfVertices;					

	xyzTextureVertex*  vertices = new xyzTextureVertex[numOfVertices];	//vertex array
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

			indicies[iCounter] = 0 + vCounter;
			indicies[iCounter + 1] = 1 + vCounter;
			indicies[iCounter + 2] = 2 + vCounter;
			indicies[iCounter + 3] = 2 + vCounter;
			indicies[iCounter + 4] = 1 + vCounter;
			indicies[iCounter + 5] = 3 + vCounter;
			iCounter += 6;


			vertices[vCounter + 0] = { 0.0f + x - halfX, (float)heightData[x * depth + z],														0.0f + z - halfZ, 0.0f, 0.0f };	//inline stament to check if outofbound, last to decide the u and v its texture
			vertices[vCounter + 1] = { 1.0f + x - halfX, (float)heightData[(x + 1 >= width? x : x+1) * depth + z],								0.0f + z - halfZ, 1.0f, 0.0f };
			vertices[vCounter + 2] = { 0.0f + x - halfX, (float)heightData[x * depth + (z + 1 >= depth ? z : z + 1)],							1.0f + z - halfZ, 0.0f, 1.0f };		
			vertices[vCounter + 3] = { 1.0f + x - halfX, (float)heightData[(x + 1 >= width? x : x+1) * depth + (z + 1 >= depth ? z : z+1)]	,	1.0f + z - halfZ, 1.0f, 1.0f };
			vCounter += 4;
		}
	}

	

	//create the to be drawn vertex buffer
	if (!SUCCEEDED(device->CreateVertexBuffer(sizeOfVertices,
		0, FVF_VERTEX_TEXTURESTRUCTURE,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		printf("failed creating vertex buffer... \n");
		return false;
	}

	//create the index buffer for the to be drawn vertices
	if (!SUCCEEDED(device->CreateIndexBuffer(sizeOfIndices,
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &indexBuffer, NULL)))
	{
		printf("failed creating index buffer... \n");
		return false;
	}

	//insert the vertices into the to be drawn vertexbuffer
	VOID* pVertices;
	if (!SUCCEEDED(vertexBuffer->Lock(0, sizeOfVertices, (void**)&pVertices, 0)))
	{
		printf("failed filling the vertex buffer... \n");
		return false;
	}
	memcpy(pVertices, vertices, sizeOfVertices);
	vertexBuffer->Unlock();


	//insert the indecis into the to be drawn indexbuffer
	VOID* pIndicies;
	if (!SUCCEEDED(indexBuffer->Lock(0, sizeOfIndices, (void**)&pIndicies, 0)))
	{
		printf("failed filling the index buffer... \n");
		return false;
	}
	memcpy(pIndicies, indicies, sizeOfIndices);
	indexBuffer->Unlock();

	printf("Terrain vertexbuffers succefully created...\n");
	
	//get the texture
	D3DXCreateTextureFromFile(device, _textureName.c_str(), &texture);
	if (!texture)
	{
		MessageBox(NULL, "failed initialising texture", NULL, NULL);
		return false;
	}

	return true;
}



void Terrain::Draw(LPDIRECT3DDEVICE9 device)
{
	if (vertexBuffer != NULL && indexBuffer != NULL && texture != NULL) 
		{
			device->SetTexture(0, texture);
			device->SetStreamSource(0, vertexBuffer, 0, sizeof(xyzTextureVertex));
			device->SetIndices(indexBuffer);
			device->SetFVF(FVF_VERTEX_TEXTURESTRUCTURE);

			device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, primCount);
		}
}



void Terrain::CleanUp()
{
	for (auto it = vertexBuffers.begin(); it != vertexBuffers.end(); it++)
	{
		if ((*it) != NULL)
		{
			(*it)->Release();
			(*it) = NULL;
		}
	}

	vertexBuffers.clear();

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

bool Terrain::LoadBMP(char* argFileName)
{

	HDC lhdcDest;						//Handle to Device Context (Windows GDI)
	HANDLE hbmp;						//Handle to an object (standard handle)
	HINSTANCE hInst = NULL;				//Handle to an instance (instance of the window)

						   
	lhdcDest = CreateCompatibleDC(NULL); //Create a memory device context compatible with the specified device (NULL)
	if (lhdcDest == NULL)
	{
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		return false;		//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(hInst, argFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		char s[100];
		wsprintf(s, "Can't find HeightMask %s", argFileName);
		MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
		return false;		//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.

	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);

	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAP bm;
	//The GetObject function retrieves information for the specified graphics object
	//bm is cast to a "void*" because GetObject function doesn't 'know' it's format 
	//(don't know what it is, but just put it in that buffer)
	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Store the width and height of the heightmap
	int width = bm.bmWidth;
	int height = bm.bmHeight;


	//Create an array to hold all the heightdata
	//WHY is a BYTE array used, and not e.g. a INT array?
	//WHY "*3"?
	heightData = new BYTE[width * height];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int itW = 0; itW < width; itW++)
	{
		for (int itH = 0; itH < height; itH++)
		{
			heightData[itW * height + itH] = GetRValue(GetPixel(lhdcDest, itW, itH));

			//printf("heightdata width %d, height %d, x %d, y %d: %d \n", width, height, itW, itH, heightData[itW * height + itH]);

		}
		//How to optimize this function? (hint: heightmaps are grayscale BMP's)	
	}
	return true;
}