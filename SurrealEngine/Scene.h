#ifndef SCENE_H_
#define SCENE_H_


#include <d3dx9.h>
#include <cstdint>							//voor uint32_t'
#include <Windows.h>

class Scene
{
public:
	Scene(D3DXVECTOR3, D3DXVECTOR3);
	virtual ~Scene();

	virtual void SetupMatrices(LPDIRECT3DDEVICE9);
	virtual uint32_t GetId();
	
private:
	uint32_t id;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 up;


	D3DXMATRIX world;
	LPDIRECT3DDEVICE9 device;
	FLOAT angle;

};

#endif // SCENE_H_