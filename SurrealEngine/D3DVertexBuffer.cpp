#include "D3DVertexBuffer.h"



D3DVertexBuffer::D3DVertexBuffer()
{
	vertexBuffer = NULL;
	indexBuffer = NULL;

	primCount = 0;
	vertexCount = 0;
}


D3DVertexBuffer::~D3DVertexBuffer()
{
	CleanUp();
}

void D3DVertexBuffer::Draw(LPDIRECT3DDEVICE9 device)
{
	if (device != NULL && vertexBuffer != NULL && indexBuffer != NULL)
	{
		device->SetStreamSource(0, vertexBuffer, 0, sizeof(xyzTextureVertex));
		device->SetIndices(indexBuffer);
		device->SetFVF(FVF_TEXTUREDVERTEX_STRUCTURE);



		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, primCount);
	}
}

bool D3DVertexBuffer::Init(LPDIRECT3DDEVICE9 device, int _primCount, int _vertexCount, xyzTextureVertex * vertices, WORD * indices, int sizeOfVertices, int sizeOfIndices)
{
	primCount = _primCount;
	vertexCount = _vertexCount;

	// create the to be drawn vertex buffer
	if (!SUCCEEDED(device->CreateVertexBuffer(sizeOfVertices,
		0, FVF_TEXTURED_NORMAL_VERTEX_STRUCTURE,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		printf("failed creating vertex buffer... \n");
		return false;
	}

	// create the index buffer for the to be drawn vertices
	if (!SUCCEEDED(device->CreateIndexBuffer(sizeOfIndices,
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &indexBuffer, NULL)))
	{
		printf("failed creating index buffer... \n");
		return false;
	}

	// insert the vertices into the to be drawn vertexbuffer
	VOID* pVertices;
	if (!SUCCEEDED(vertexBuffer->Lock(0, sizeOfVertices, (void**)&pVertices, 0)))
	{
		printf("failed filling the vertex buffer... \n");
		return false;
	}
	memcpy(pVertices, vertices, sizeOfVertices);
	vertexBuffer->Unlock();


	// insert the indecis into the to be drawn indexbuffer
	VOID* pIndices;
	if (!SUCCEEDED(indexBuffer->Lock(0, sizeOfIndices, (void**)&pIndices, 0)))
	{
		printf("failed filling the index buffer... \n");
		return false;
	}
	memcpy(pIndices, indices, sizeOfIndices);
	indexBuffer->Unlock();

	return true;

}

void D3DVertexBuffer::CleanUp()
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
}
