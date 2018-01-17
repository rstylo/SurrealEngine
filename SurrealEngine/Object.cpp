#include "Object.h"
#include "DirectXRenderer.h"

struct ObjectVertex
{
	FLOAT x, y, z;      // 3d positie
	FLOAT tu, tv;        // kleur

	ObjectVertex() {}
	ObjectVertex(float _x, float _y, float _z, float _tu, float _tv)
	{
		x = _x;
		y = _y;
		z = _z;

		tu = _tu;
		tv = _tv;
	}
};

Object::Object(std::string _objectName)
	: Resource(), initialised(false)
{
	objectName = _objectName;
	textureName = "texture1.jpg";
}


Object::~Object()
{
	CleanUp();
}

void Object::CleanUp()
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

	initialised = false;
}

bool Object::Init(Renderer* renderer)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

		if (initialised == false)
		{
			CleanUp();

			//get the texture
			D3DXCreateTextureFromFile(device, textureName.c_str(), &texture);
			if (!texture)
			{
				MessageBox(NULL, "failed initialising texture @ object", NULL, NULL);
				initialised = false;
				return false;
			}

			vertexBuffer = NULL;

			indexBuffer = NULL;

			const int numOfVertices = 8;										//8 vertices voor een cube
			const int numOfIndices = 6 * 6;										//6 indicies per quad

			primCount = 6 * 2;													//2 triangles per quad
			vertexCount = numOfVertices;

			ObjectVertex* vertices = new ObjectVertex[numOfVertices];			//vertex array
										//vertex-index array

			int sizeOfVertices = numOfVertices * sizeof(ObjectVertex);			//sizeof the vertex array
			int sizeOfIndices = numOfIndices * sizeof(WORD);					//sizeof the indexarray



			vertices[0] = {	0.0f,	0.0f,	0.0f,	0.0f,	0.0f };
			vertices[1] = { 1.0f,	0.0f,	0.0f,	1.0f,	0.0f };
			vertices[2] = { 0.0f,	1.0f,	0.0f,	0.0f,	1.0f };
			vertices[3] = { 1.0f,	1.0f,	0.0f,	1.0f,	1.0f };

			vertices[4] = { 0.0f,	0.0f,	1.0f,	0.0f,	0.0f };
			vertices[5] = { 1.0f,	0.0f,	1.0f,	1.0f,	0.0f };
			vertices[6] = { 0.0f,	1.0f,	1.0f,	0.0f,	1.0f };
			vertices[7] = { 1.0f,	1.0f,	1.0f,	1.0f,	1.0f };

			WORD* indicies = new WORD[numOfIndices]
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


			if (!SUCCEEDED(device->CreateVertexBuffer(sizeOfVertices,
				0, FVF_VERTEXSTRUCTURE,
				D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
			{
				printf("failed creating vertex buffer %d... \n");
				return false;
			}

			if (!SUCCEEDED(device->CreateIndexBuffer(sizeOfIndices,
				D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
				D3DPOOL_MANAGED, &indexBuffer, NULL)))
			{
				printf("failed creating index buffer %d... \n");
				return false;
			}

			VOID* pVertices;
			if (!SUCCEEDED(vertexBuffer->Lock(0, sizeOfVertices, (void**)&pVertices, 0)))
			{
				printf("failed filling the vertex buffer %d... \n");
				return false;
			}
			memcpy(pVertices, vertices, sizeOfIndices);
			vertexBuffer->Unlock();

			VOID* pIndicies;
			if (!SUCCEEDED(indexBuffer->Lock(0, sizeof(indicies), (void**)&pIndicies, 0)))
			{
				printf("failed filling the index buffer %d... \n");
				return false;
			}

			memcpy(pIndicies, indicies, sizeof(indicies));
			indexBuffer->Unlock();




			initialised = true;
		}
		return true;
	}
	return false;
	
}

void Object::Draw(Renderer* renderer)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) 
	{

		LPDIRECT3DDEVICE9 device = *dxrenderer->GetDevice();

		if (device != NULL && texture != NULL && initialised == true)
		{

			device->SetTexture(0, texture);
			device->SetStreamSource(0, vertexBuffer, 0, sizeof(ObjectVertex));

			device->SetIndices(indexBuffer);
			device->SetFVF(FVF_VERTEXSTRUCTURE);

			device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, primCount);
			//device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //<- 
		}
	}
}

std::string Object::GetObjectName()
{
	return objectName;
}

void Object::SetTexture(std::string _textureName)
{
	textureName = _textureName;
}