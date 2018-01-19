/*! \file  Skybox.h
	\brief this class is used to draw and move the skybox texture
*/

#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <d3dx9.h>
#include <string>
#include "Transform.h"

#define FVF_VERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1) //flexible vertex format


class Skybox
{
public:
	Skybox();
	virtual ~Skybox();

	virtual bool Init(Renderer*);

	virtual void Update(Vector3);
	virtual void Create();
	virtual void Invalidate();


	virtual void SetupMatrices(Renderer*, Transform);

	virtual void Draw(Renderer*);

	virtual void SetTexture(std::string);
	virtual std::string GetTexture();

private:
	std::string textureName;

	Transform transform;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	LPDIRECT3DTEXTURE9 skyboxTexture;
	Vector3 middle;

	Logger logger;
};

#endif // !SKYBOX_H_