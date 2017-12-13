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

	for (int x = 0 - size/2; x < size/2 ; x++)													//for elke triangle strip
	{
		int i = 0;																	//beginnen bij eerste vertice
		const int numOfVertices = 400;												//elke quad heeft 4 vertices, dus 4 * 100
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;										//buffer waar deze strip in komt
		xyzColorVertex  vertices[numOfVertices];									//vertice array voor de strip aanmaken

		for (int z = 0 - size/2; z < size/2; z++) {									//voor elke quad in de triangle strip, zijn de volgende vertices
			vertices[i] =	{ 0.0f + x, 0.0f + 0, 0.0f + z, 0x0FF000FF };			
			vertices[i + 1] = { 1.0f + x, 0.0f + 0, 0.0f + z, 0x009933FF };
			vertices[i + 2] = { 0.0f + x, 0.0f + 0, 1.0f + z, 0x0FF933FF };
			vertices[i + 3] = { 1.0f + x, 0.0f + 0, 1.0f + z, 0x009FF3FF };
			i += 4;																	//volgende quad begint hier
		}

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
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 300);												//<- 3 per quad in de strip
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