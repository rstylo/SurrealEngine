#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <d3dx9.h>
#include <iostream>
#include <map>
#include <list>
#include <string>

#define FVF_NORMALVERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_NORMAL) //flexible vertex format
#define FVF_VERTEX_TEXTURESTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1) //flexible vertex format




class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	virtual void SetMapAndTexture(std::string heightMapFileName, std::string _textureName);

	virtual bool InitWithTexture(LPDIRECT3DDEVICE9);	//
	virtual void Invalidate();



	virtual void SetupMatrices(LPDIRECT3DDEVICE9 device);
	//virtual bool InitWithColor(LPDIRECT3DDEVICE9);
	virtual void Draw(LPDIRECT3DDEVICE9);

	
private:

	virtual void CleanUp();
	virtual bool LoadBMP(std::string);

	std::string heightMapFileName;
	std::string textureName;
	
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;				
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	
	LPDIRECT3DTEXTURE9 texture;
	
	BYTE* heightData;

	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;

	bool initialized;

	int width;
	int depth;
	int primCount;
	int vertexCount;

};


#endif // !TERRAIN_H_
