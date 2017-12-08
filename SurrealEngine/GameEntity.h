#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <d3dx9.h>
#include <string>

class GameEntity
{
public:
	GameEntity();
	~GameEntity();
	void Init();
	void SetRenderDevice(LPDIRECT3DDEVICE9);
	HRESULT SetMesh(std::string);
	void Cleanup();
	void Draw();
	void SetupMatrices();

private:
	std::string path;
	std::string fileName;

	//mischien is het niet handig om alle d3d9 dingen hier op te slaan :P
	LPDIRECT3DDEVICE9 g_pd3dDevice;
	LPD3DXMESH          g_pMesh; // Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials; // Materials for our mesh
	LPDIRECT3DTEXTURE9* g_pMeshTextures; // Textures for our mesh
	DWORD               g_dwNumMaterials;   // Number of mesh materials

};

#endif // !GAMEENTITY_H_