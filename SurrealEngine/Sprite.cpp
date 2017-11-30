#include "Sprite.h"



Sprite::Sprite()
	:Resource("Sprite"), initialized(false)
{
	color = D3DCOLOR_ARGB(255, 255, 255, 255); //witte kleur, betekent dat je de origineele kleuren van je sprite(image) over neemt
}

Sprite::~Sprite()
{
	if (sprite != NULL)
	{
		sprite->Release();
		sprite = NULL;
	}

	if (tex != NULL)
	{
		tex->Release();
		tex = NULL;
	}
}

bool Sprite::Init(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{

	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), width, height,
		D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))								
	{
		std::string s = "issue creating texture, requested image: " + file;
		MessageBox(NULL, s.c_str(), NULL, NULL);
		return false;
	}

	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite))) {
		MessageBox(NULL, "issue creating sprite", NULL, NULL);
		return false;
	}

	initialized = true;
	return true;
}

bool Sprite::IsInit()
{
	return true;
}

void Sprite::Draw(D3DXVECTOR3 position)
{
	if (sprite != NULL && tex != NULL)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		sprite->Draw(tex, NULL, NULL, &position, color);

		sprite->End();
	}
}




