#ifndef DXMANAGER_H_
#define DXMANAGER_H_


#include <d3dx9.h>
#include <iostream>
#include <string>
#include <map>

#include <cmath>

struct DxVertexBuffer						
{
	std::string name;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = NULL;	//!
	LPDIRECT3DINDEXBUFFER9 indexBuffer = NULL;

	int primCount = 0;
	int vertexCount = 0;

	bool initialized = false;
	DxVertexBuffer() {};
};

struct DxHeightMap
{
	std::string heightMapName;
	BYTE* heightData = NULL;

	int width = 0;
	int depth = 0;
	DxHeightMap() {};
};

struct DxMesh
{
	std::string meshPath;					//! mesh identifier and file location

	LPD3DXMESH          mesh = NULL;			//! Our mesh object in sysmem
	D3DMATERIAL9*       materials = NULL;		//! Materials for our mesh
	LPDIRECT3DTEXTURE9* textures = NULL;		//! Textures for our mesh
	DWORD               numOfMaterials = 0L;	//! Number of mesh materials

	bool initialized = false;
	DxMesh() {};
};

struct DxTexture
{
	std::string textureName;

	LPDIRECT3DTEXTURE9 texture = NULL;
	DxTexture() {};
};




class DxManager
{
public:
	DxManager();
	virtual ~DxManager();

	virtual bool AddTexture(DxTexture*);
	virtual DxTexture* GetTexture(std::string);
	virtual bool DeleteTexture(std::string);


	virtual bool AddMesh(DxMesh*);
	virtual DxMesh* GetMesh(std::string);
	virtual bool DeleteMesh(std::string);

	virtual bool AddHeightMap(DxHeightMap*);
	virtual DxHeightMap* GetHeightMap(std::string);
	virtual bool DeleteHeightMap(std::string);

	virtual bool AddVertexBuffer(DxVertexBuffer*);
	virtual DxVertexBuffer* GetVertexBuffer(std::string);
	virtual bool DeleteVertexBuffer(std::string);

private:
	
	std::map<std::string, DxTexture*> textures;
	std::map<std::string, DxMesh*> meshes;
	std::map<std::string, DxHeightMap*> heightMaps;
	std::map<std::string, DxVertexBuffer*> vertexBuffers;

};

#endif //! DXMANAGER_H_