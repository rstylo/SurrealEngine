#include "Object.h"



Object::Object(int _numVertices, int _primCount)
{
	numVertices = _numVertices;
	primCount = _primCount;
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


void Object::Draw(LPDIRECT3DDEVICE9 device)
{
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(ObjectVertex));
	device->SetIndices(indexBuffer);
	device->SetFVF(FVF_VERTEXSTRUCTURE);

	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, primCount);
	//device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //<- 
}