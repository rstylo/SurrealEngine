#ifndef DXMANAGER_H_
#define DXMANAGER_H_


#include <d3dx9.h>
#include <iostream>
#include <string>
#include <map>

#include <cmath>

struct DxVertexBuffer						
{
	std::string name;								//! identifier

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = NULL;	//! vertexbuffer holding vertiecs
	LPDIRECT3DINDEXBUFFER9 indexBuffer = NULL;		//! indexbuffer holding indices

	int primCount = 0;								//! primitive count of the to draw vertexbuffer
	int vertexCount = 0;							//! count of vertices

	bool initialized = false;						
	DxVertexBuffer() {};
};

struct DxHeightMap
{
	std::string heightMapName;						//! file name of the heightmap and identifier
	BYTE* heightData = NULL;						//! data in which loaded data from given map is laoded into (0-255)

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

	virtual bool AddTexture(DxTexture*);				//! add new dxtexture pointer for managing
	virtual DxTexture* GetTexture(std::string);
	virtual bool DeleteTexture(std::string);			//! delete a texture with given name if existing


	virtual bool AddMesh(DxMesh*);						//! add new dxmesh pointer for managing
	virtual DxMesh* GetMesh(std::string);
	virtual bool DeleteMesh(std::string);				//! delete a mesh with given name if existing

	virtual bool AddHeightMap(DxHeightMap*);			//! add new dxheightmap pointer for managing
	virtual DxHeightMap* GetHeightMap(std::string);
	virtual bool DeleteHeightMap(std::string);			//! delete a heightmap with given name if existing

	virtual bool AddVertexBuffer(DxVertexBuffer*);			//! add new dxvertexbuffer pointer for managing
	virtual DxVertexBuffer* GetVertexBuffer(std::string);
	virtual bool DeleteVertexBuffer(std::string);			//! delete a vertebuffer with given name if existing

private:
	
	std::map<std::string, DxTexture*> textures;				//!
	std::map<std::string, DxMesh*> meshes;
	std::map<std::string, DxHeightMap*> heightMaps;
	std::map<std::string, DxVertexBuffer*> vertexBuffers;

};

#endif //! DXMANAGER_H_