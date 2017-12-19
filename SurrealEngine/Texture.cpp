#include "Texture.h"
#include <d3dx9.h>

Texture::Texture(LPDIRECT3DDEVICE9* _device) : Resource()
{
	device = *_device;
	meshTextures = NULL;
}

Texture::~Texture()
{

}

void Texture::Create(std::string file)
{
	if (!SetTexture(file))
	{
		MessageBox(NULL, "Mesh not loaded", NULL, NULL);
	}
}

boolean Texture::SetTexture(std::string _fileName)
{
	std::string file = "Assets\\" + _fileName;

	meshTextures = new LPDIRECT3DTEXTURE9;
	if (meshTextures == NULL)
		return FALSE;

	if (FAILED(D3DXCreateTextureFromFileA(device, file.c_str(), &meshTextures[0])))
	{
		MessageBox(NULL, "Could not find texture map", NULL, NULL);
		return FALSE;
	}
	return TRUE;
}

void Texture::Draw()
{
	device->SetTexture(0, meshTextures[0]);
}