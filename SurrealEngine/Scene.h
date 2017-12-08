#ifndef SCENE_H_
#define SCENE_H_


#include <d3dx9.h>
#include <cstdint>							//voor uint32_t'
#include <Windows.h>
#include <map>

class Terrain;
class Camera;

class Scene
{
public:
	Scene(D3DXVECTOR3, D3DXVECTOR3);
	virtual ~Scene();

	virtual void SetupMatrices(LPDIRECT3DDEVICE9, int);
	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual void SetupTerrain(LPDIRECT3DDEVICE9);
	virtual uint32_t GetId();

	virtual void AddCamera(int, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	
private:
	uint32_t id;


private:
	Terrain* terrain;

	std::map<int, Camera*> cameras;

};

#endif // SCENE_H_