#ifndef  D3DTEXTURE_H_
#define  D3DTEXtURE_H_

#include <d3dx9.h>
#include <string>

class Renderer;
class D3DTexture
{
public:
	D3DTexture();
	virtual ~D3DTexture();

	virtual bool Init(LPDIRECT3DDEVICE9 device);
	virtual void Draw(LPDIRECT3DDEVICE9 device);

	virtual void CleanUp();

	virtual std::string GetTextureName();

	virtual LPDIRECT3DTEXTURE9 GetDxTexture();
	virtual void SetTextureName(std::string);

	
private:
	LPDIRECT3DTEXTURE9 texture;
	std::string textureName;
};

#endif // ! D3DTEXTURE_H_