#include "Skybox.h"

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	FLOAT tu, tv;
};


Skybox::Skybox()
{
	skyboxTexture = NULL;
	vertexBuffer = NULL;
}


Skybox::~Skybox()
{

}

bool Skybox::Init(LPDIRECT3DDEVICE9 device, std::string _texture)
{
	// Use D3DX to create a texture from a file based image
	if (FAILED(D3DXCreateTextureFromFile(device, _texture.c_str(), &skyboxTexture)))
	{
		MessageBox(NULL, "Could not find skybox texture", NULL, NULL);
		return false;
	}

	if (FAILED(device->CreateVertexBuffer(14 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_XYZ | D3DFVF_TEX1,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		MessageBox(NULL, "Could not create vertexbuffer", NULL, NULL);
		return false;
	}

	if (FAILED(device->CreateIndexBuffer(36 * sizeof(short), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL))) {
		MessageBox(NULL, "Could not create indexbuffer", NULL, NULL);
		return false;
	}

	return true;
}
void Skybox::Update(D3DVECTOR position)
{
	middle.x = position.x;
	middle.y = position.y;
	middle.z = position.z;
}

void Skybox::Create()
{
	int size = 100;

	CUSTOMVERTEX* vertices;
	if (FAILED(vertexBuffer->Lock(0, 0, (void**)&vertices, 0))) {
		MessageBox(NULL, "Could not lock vertexbuffer", NULL, NULL);
		return;
	}

	vertices[0].position = -D3DXVECTOR3(-size, -size, size);
	vertices[1].position = -D3DXVECTOR3(-size, size, size);
	vertices[2].position = -D3DXVECTOR3(size, -size, size);
	vertices[3].position = -D3DXVECTOR3(size, size, size);
	vertices[4].position = -D3DXVECTOR3(size, -size, -size);
	vertices[5].position = -D3DXVECTOR3(size, size, -size);
	vertices[6].position = -D3DXVECTOR3(-size, -size, -size);
	vertices[7].position = -D3DXVECTOR3(-size, size, -size);

	vertices[8].position = -D3DXVECTOR3(-size, size, size);		//vertex 1 // top
	vertices[9].position = -D3DXVECTOR3(-size, size, -size);		//vertex 7

	vertices[10].position = -D3DXVECTOR3(-size, -size, size);	//vertex 0 // bottom
	vertices[11].position = -D3DXVECTOR3(-size, -size, -size);	//vertex 6

	vertices[12].position = -D3DXVECTOR3(-size, -size, size);	//vertex 0
	vertices[13].position = -D3DXVECTOR3(-size, size, size);		//vertex 1



	vertices[0].tu = 0.00f;
	vertices[0].tv = (float)1025 / 3072;
	vertices[1].tu = 0.00f;
	vertices[1].tv = (float)2047 / 3072;
	vertices[2].tu = (float)1025 / 4096;
	vertices[2].tv = (float)1025 / 3072;
	vertices[3].tu = (float)1025 / 4096;
	vertices[3].tv = (float)2047 / 3072;
	vertices[4].tu = (float)2047 / 4096;
	vertices[4].tv = (float)1025 / 3072;
	vertices[5].tu = (float)2047 / 4096;
	vertices[5].tv = (float)2047 / 3072;
	vertices[6].tu = 0.75f;
	vertices[6].tv = (float)1025 / 3072;
	vertices[7].tu = 0.75f;
	vertices[7].tv = (float)2047 / 3072;

	vertices[12].tu = 1.00f;					// vertex 0 with other texture coordinate
	vertices[12].tv = (float)1025 / 3072;
	vertices[13].tu = 1.00f;					// vertex 1 with other texture coordinate
	vertices[13].tv = (float)2047 / 3072;

	vertices[8].tu = (float)1025 / 4096;		// bottom 
	vertices[8].tv = (float)3071 / 3072;		// vertex 1 with other texture coordinate
	vertices[9].tu = (float)2047 / 4096;
	vertices[9].tv = (float)3071 / 3072;		// vertex 7 with other texture coordinate

	vertices[10].tu = (float)1025 / 4096;		// top
	vertices[10].tv = (float)1 / 3072;			// vertex 0 with other texture coordinate
	vertices[11].tu = (float)2047 / 4096;
	vertices[11].tv = (float)1 / 3072;			// vertex 6 with other texture coordinate

	vertexBuffer->Unlock();

	short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,

		2, 3, 4,	// side 2
		4, 3, 5,

		4, 5, 6,	// side 3
		6, 5, 7,

		12, 13, 6,	// side 4
		6, 13, 7,

		3, 8, 9,	// side bottom
		3, 5, 9,

		2, 10, 4,	// side top
		4, 10, 11,
	};
	VOID* pIndices;
	if (FAILED(indexBuffer->Lock(0, 0, (void**)&pIndices, 0))) {
		MessageBox(NULL, "Could not lock indexbuffer", NULL, NULL);
		return;
	}
	memcpy(pIndices, indices, sizeof(indices));
	indexBuffer->Unlock();
}

void Skybox::SetupMatrices(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX worldMtrx;
	D3DXMatrixTranslation(&worldMtrx, middle.x, middle.y, middle.z);
	device->SetTransform(D3DTS_WORLD, &worldMtrx);
}

void Skybox::Draw(LPDIRECT3DDEVICE9 device)
{
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	device->SetTexture(0, skyboxTexture);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTSS_COLORARG1);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	device->SetStreamSource(0, vertexBuffer, 0, sizeof(CUSTOMVERTEX));
	device->SetIndices(indexBuffer);
	device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 14, 0, 12);
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}