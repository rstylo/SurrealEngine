#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Resource.h"
#include <d3dx9.h>

class Texture : public Resource
{
public:
	Texture(LPDIRECT3DDEVICE9*);
	~Texture();
	virtual void Create(std::string);
	boolean SetTexture(std::string);
	void Draw();

private:
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3DTEXTURE9* meshTextures; // Textures for our mesh
};

#endif // !TEXTURE_H_
