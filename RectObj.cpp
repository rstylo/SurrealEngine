#include "RectObj.h"



RectObj::RectObj()
	:Object(INDICIESSIZE, 12)
{

	

}


RectObj::~RectObj()
{
}

bool RectObj::EditObject(LPDIRECT3DDEVICE9 device, float x, float y, float z, float scaleX, float scaleY, float scaleZ)
{
	vertexBuffer = NULL;

	indexBuffer = NULL;

	//1x1 cube vertices
	vertices[0] = { 0.0f, 0.0f, 0.0f, 0x00FF0000 };
	vertices[1] = { 1.0f, 0.0f, 0.0f, 0x00800000 };
	vertices[2] = { 0.0f, 1.0f, 0.0f, 0x00FFFF00 };
	vertices[3] = { 1.0f, 1.0f,  0.0f, 	0x00000000 };

	initialized = false;
	vertices[4] = { 0.0f, 0.0f, 1.0f, 0x00FF0000 };
	vertices[5] = { 1.0f, 0.0f,  1.0f, 0x00800000 };
	vertices[6] = { 0.0f, 1.0f, 1.0f, 0x00FFFF00 };
	vertices[7] = { 1.0f, 1.0f,  1.0f, 0x00000000 };

	for (int it = 0; it < VERTICESSIZE; it++)	//move
	{
		vertices[it].x += x;
		vertices[it].y += y;
		vertices[it].z += z;
	}
	
	//origin vertices[0]
	vertices[1].x *= scaleX;
	vertices[2].y *= scaleY;
	vertices[3].x *= scaleX;
	vertices[3].y *= scaleY;

	vertices[4].z *= scaleZ;
	vertices[5].x *= scaleX;
	vertices[5].z *= scaleZ;
	vertices[6].y *= scaleY;
	vertices[6].z *= scaleZ;
	vertices[7].x *= scaleX;
	vertices[7].y *= scaleY;
	vertices[7].z *= scaleZ;

	WORD indicies[INDICIESSIZE] =
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

		//bottom face
		4, 5, 0,
		0, 5, 1,

		//top face
		2, 3, 6,
		6, 3, 7
	};

	if (!SUCCEEDED(device->CreateVertexBuffer(VERTICESSIZE * sizeof(ObjectVertex),
		0, FVF_VERTEXSTRUCTURE,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		printf("failed creating vertex buffer %d... \n");
		return false;
	}

	if (!SUCCEEDED(device->CreateIndexBuffer(INDICIESSIZE * sizeof(WORD),
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

	return true;
}

