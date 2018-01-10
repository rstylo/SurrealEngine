#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <d3dx9.h>
#include <string>

#define FVF_VERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1) //flexible vertex format


class Skybox
{
public:
	Skybox();
	virtual ~Skybox();

	virtual bool Init(LPDIRECT3DDEVICE9, std::string);

	virtual void Update(D3DVECTOR);
	virtual void Create();


	virtual void SetupMatrices(LPDIRECT3DDEVICE9 device);

	virtual void Draw(LPDIRECT3DDEVICE9);

private:
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	LPDIRECT3DTEXTURE9 skyboxTexture;
	D3DVECTOR middle;

};

#endif // !SKYBOX_H_