#include "Object.h"



Object::Object()
{
	//

}


Object::~Object()
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

bool Object::Init(LPDIRECT3DDEVICE9 device, float x, float y, float z, float size)
{
	
	const int numOfVertices = 8;
	const int numOfIndicies = 36;

	ObjectVertex  vertices[numOfVertices] =
	{
		{ -1.0f, 1.0f, -1.0f, 0x009933FF },		//0
		{ 1.0f, 1.0f,  -1.0f, 0x00ff8000 },		//1
		{ -1.0f, -1.0f, -1.0f, 0x00ff8000 },	//2
		{ 1.0f, -1.0f,  -1.0f, 0x004c2600 },	//3
		
		{ -1.0f, 1.0f, 1.0f, 0x009933FF },		//4
		{ 1.0f, 1.0f,  1.0f, 0x00004c26 },		//5
		{ -1.0f, -1.0f, 1.0f, 0x004c2600 },		//6
		{ 1.0f, -1.0f,  1.0f, 0x009933FF },		//7

	};


	WORD indicies[numOfIndicies] =
	{
		
		//front face
		0, 1, 2,
		2, 1, 3,

		//back face
		5, 4, 7,
		7, 4, 6,

		//rightface
		1, 5, 3,
		3, 5, 7,

		//left face
		4, 0, 6,
		6, 0, 2,

		//top face
		4, 5, 0,
		0, 5, 1,

		//bottom face
		2, 3, 6,
		6, 3, 7
	};
	
	
	/*const int numOfVertices = 4;
	const int numOfIndicies = 12;

	ObjectVertex  vertices[numOfVertices] =
	{
		{ -3.0f, 0.0f, -2.0f, 0x009933FF },		//0
		{ 3.0f, 0.0f,  -2.0f, 0x00ff8000 },		//1
		{ 0.0f, 3.0f, -1.0f, 0x00ff8000 },	//2
		{ 0.0f, 0.0f,  1.0f, 0x004c2600 },	//3

	};

	WORD indicies[numOfIndicies] =
	{
		//front face
		0, 1, 2,

		//right
		2, 1, 3,

		//left
		3, 2, 0,
	

		//bottom
		0, 1, 3

	};
	*/
	
	
	if (!SUCCEEDED(device->CreateVertexBuffer(numOfVertices * sizeof(ObjectVertex),
		0, FVF_VERTEXSTRUCTURE,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		return false;
	}

	if (!SUCCEEDED(device->CreateIndexBuffer(numOfIndicies * sizeof(WORD),
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &indexBuffer, NULL)))
	{
		return false;
	}

	VOID* pVertices;
	if (!SUCCEEDED(vertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return false;
	memcpy(pVertices, vertices, sizeof(vertices));
	vertexBuffer->Unlock();

	VOID* pIndicies;
	if (!SUCCEEDED(indexBuffer->Lock(0, sizeof(indicies), (void**)&pIndicies, 0)))
		return false;
	memcpy(pIndicies, indicies, sizeof(indicies));
	indexBuffer->Unlock();

	return true;
}

void Object::Draw(LPDIRECT3DDEVICE9 device)
{
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(ObjectVertex));
	device->SetIndices(indexBuffer);
	device->SetFVF(FVF_VERTEXSTRUCTURE);

	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 36, 0, 12);
	//device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //<- 
}