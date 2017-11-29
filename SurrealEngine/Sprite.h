#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>
#include <string>

#include "Resource.h"

class Sprite : public Resource
{
public:
	Sprite();
	virtual ~Sprite();

	virtual bool Init(LPDIRECT3DDEVICE9, std::string, int, int);
	virtual bool IsInit();
	virtual void Draw(D3DXVECTOR3);


private:
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;

	D3DCOLOR color;

	bool initialized;

};

#endif // SPRITE_H_
