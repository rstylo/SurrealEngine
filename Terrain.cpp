#include "Terrain.h"



Terrain::Terrain()
	:primCount(0), vertexCount(0)
{
	
}

Terrain::~Terrain()
{
	CleanUp();

	delete heightData;
}

bool Terrain::Init(LPDIRECT3DDEVICE9 device, const int width, const int depth)
{

	const int numOfVertices = width * depth * 4;
	const int numOfIndices = width * depth * 6;

	primCount = width * depth * 2;
	vertexCount = numOfVertices;

	//xyzColorVertex*  vertices = new xyzColorVertex[numOfVertices];		// vetice array maken voor de map			
	//WORD* indicies = new WORD[numOfIndices];										//6 indises per quad

	xyzColorVertex  vertices[100 * 100 * 4];
	WORD indicies[100 * 100 * 6];

	int vCounter = 0;
	int iCounter = 0;

	int halfX = width / 2 + 1;
	int halfZ = depth / 2 + 1;
	
	//iterate door x en z as en insert de bij behorende data
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

			vertices[vCounter] =	 { 0.0f + x - halfX, (float)heightData[x * depth + z],				0.0f + z - halfZ,	0x000ff000 };
			vertices[vCounter + 1] = { 1.0f + x - halfX, (float)heightData[(x + 1) * depth + z],		0.0f + z - halfZ,	0x00009900 };
			vertices[vCounter + 2] = { 0.0f + x - halfX, (float)heightData[x * depth + z + 1],			1.0f + z - halfZ,	0x00006600 };
			vertices[vCounter + 3] = { 1.0f + x - halfX, (float)heightData[(x + 1) * depth + z + 1]	,	1.0f + z - halfZ,	0x00003300 };
			vCounter += 4;
		}
	}

	if (!SUCCEEDED(device->CreateVertexBuffer(numOfVertices * sizeof(xyzColorVertex),
		0, FVF_VERTEXSTRUCTURE,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		printf("failed creating vertex buffer %d... \n");
		return false;
	}

	if (!SUCCEEDED(device->CreateIndexBuffer(numOfIndices * sizeof(WORD),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &indexBuffer, NULL)))
	{
		printf("failed creating index buffer %d... \n");
		return false;
	}

	VOID* pVertices;
	if (!SUCCEEDED(vertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	{
		printf("failed filling the vertex buffer %d... \n");
		return false;
	}
	memcpy(pVertices, vertices, sizeof(vertices));
	vertexBuffer->Unlock();

	VOID* pIndicies;
	if (!SUCCEEDED(indexBuffer->Lock(0, sizeof(indicies), (void**)&pIndicies, 0)))
	{
		printf("failed filling the index buffer %d... \n");
		return false;
	}

	memcpy(pIndicies, indicies, sizeof(indicies));
	indexBuffer->Unlock();

	printf("Terrain vertexbuffers succefully created...\n");
	return true;
}

void Terrain::Draw(LPDIRECT3DDEVICE9 device)
{
	if (vertexBuffer != NULL && indexBuffer != NULL) {
		device->SetStreamSource(0, vertexBuffer, 0, sizeof(xyzColorVertex));
		device->SetIndices(indexBuffer);
		device->SetFVF(FVF_VERTEXSTRUCTURE);

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
}

bool Terrain::LoadBMP(char* argFileName)
{

	HDC lhdcDest;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp;	//Handle to an object (standard handle)
	HINSTANCE hInst = NULL;//Handle to an instance (instance of the window)

						   //Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
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