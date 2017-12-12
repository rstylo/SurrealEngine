#include "Terrain.h"



Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	CleanUp();
}



bool Terrain::Init(LPDIRECT3DDEVICE9 device,  const int size)
{
	vertexBuffers.clear();


	for (int x = 0; x < size ; x++)													//for elke triangle strip
	{
		int i = 0;																	//beginnen bij eerste vertice
		const int numOfVertices = 4 * 512;											//elke quad heeft 4 vertices, dus 4 * 256
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;										//buffer waar deze strip in komt
		xyzColorVertex  vertices[numOfVertices];									//vertice array voor de strip aanmaken

		for (int z = 0; z < size; z++) 
		{																					//voor elke quad in de triangle strip, zijn de volgende vertices
			vertices[i] =	{ 0.0f + x, 0.0f + heightData[x,z], 0.0f + z, 0x0FF000FF };			
			vertices[i + 1] = { 1.0f + x, 0.0f + heightData[x,z+1], 0.0f + z, 0x009933FF };
			vertices[i + 2] = { 0.0f + x, 0.0f + heightData[x+1,z], 1.0f + z, 0x0FF933FF };
			vertices[i + 3] = { 1.0f + x, 0.0f + +heightData[x+1,z+1], 1.0f + z, 0x009FF3FF };
			i += 4;																				//volgende quad begint hier
		} 

		/*for (int z = 0; z < size; z++)
		{																					//voor elke quad in de triangle strip, zijn de volgende vertices
		vertices[i] =	{ 0.0f + x, 0.0f, 0.0f + z, 0x0FF000FF };
		vertices[i + 1] = { 1.0f + x, 0.0f, 0.0f + z, 0x009933FF };
		vertices[i + 2] = { 0.0f + x, 0.0f, 1.0f + z, 0x0FF933FF };
		vertices[i + 3] = { 1.0f + x, 0.0f, 1.0f + z, 0x009FF3FF };
		i += 4;																				//volgende quad begint hier
		} */

		if (!SUCCEEDED(device->CreateVertexBuffer(numOfVertices * sizeof(xyzColorVertex),
			0, FVF_VERTEXSTRUCTURE,
			D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
		{
			CleanUp();
			printf("Failed creating vertexBuffers(1)!\n");
			return false;
			
		}

		VOID* pVertices;
		if (!SUCCEEDED(vertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		{
			CleanUp();
			printf("Failed creating vertexBuffers(2)!\n");
			return false;
		}
		memcpy(pVertices, vertices, sizeof(vertices));
		vertexBuffer->Unlock();
		
		vertexBuffers.push_back(vertexBuffer);																	//voegt de vertexbuffer voor de huidige strip toe aan het geheel
		
	}
	printf("Terrain vertexbuffers succefully created...\n");
	return true;
}

void Terrain::Draw(LPDIRECT3DDEVICE9 device)
{
	for (auto vertexBuffer = vertexBuffers.begin(); vertexBuffer != vertexBuffers.end(); vertexBuffer++)	//teken alle vertex buffers
	{
		
		device->SetStreamSource(0, (*vertexBuffer), 0, sizeof(xyzColorVertex));	
		device->SetFVF(FVF_VERTEXSTRUCTURE);
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 3 * 256);												//<- 3 per quad in de strip
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
	heightData = new BYTE[width, height];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int itW = 0; itW < width; itW++)
	{
		for (int itH = 0; itH < height; itH++)
		{
			heightData[itW, itH] = GetRValue(GetPixel(lhdcDest, itW, itH));

			//printf("heightdata width %d, height %d, x %d, y %d: %d \n", width, height, itW, itH, heightData[itW, itH]);

		}
		//How to optimize this function? (hint: heightmaps are grayscale BMP's)	
	}
	return true;
}