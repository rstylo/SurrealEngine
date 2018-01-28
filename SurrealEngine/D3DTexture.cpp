#include "D3DTexture.h"



D3DTexture::D3DTexture()
{

}


D3DTexture::~D3DTexture()
{
	CleanUp();
}

bool D3DTexture::Init(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateTextureFromFile(device, textureName.c_str(), &texture);
	if (!texture)
	{
		D3DXCreateTextureFromFile(device, ("..\\" + textureName).c_str(), &texture);
		if (!texture) {
			MessageBox(NULL, std::string("failed initialising texture: " + textureName).c_str(), NULL, NULL);
			return false;
		}
		return true;
	}

	return false;
}

void D3DTexture::Draw(LPDIRECT3DDEVICE9 device)
{
	//device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	//only if renderstate light is true
	if (texture != NULL)
	{
		device->SetTexture(0, texture);

		device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}
}

void D3DTexture::CleanUp()
{
	if (texture != NULL)
	{
		texture->Release();
		texture = NULL;
	}
}

std::string D3DTexture::GetTextureName()
{
	return textureName;
}

LPDIRECT3DTEXTURE9 D3DTexture::GetDxTexture()
{
	return texture;
}

void D3DTexture::SetTextureName(std::string _textureName)
{
	textureName = _textureName;
}
