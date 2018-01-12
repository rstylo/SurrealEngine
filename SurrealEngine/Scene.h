/*
* Class: Scene.h
* Description : 
* Note :
*/

#ifndef SCENE_H_
#define SCENE_H_


#include <d3dx9.h>
#include <cstdint>							//voor uint32_t'
#include <Windows.h>
#include <string>
#include <map>

#include "Transform.h"

class Terrain;
class Camera;
class Resource;
class Entity;
class InputHandler;
class Skybox;

class Scene
{
public:
	Scene(std::string);
	virtual ~Scene();

	virtual uint32_t GetId();
	virtual std::string GetName();

	virtual bool InitEntities(LPDIRECT3DDEVICE9);
	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual void Update();

	virtual void SetupView(LPDIRECT3DDEVICE9, int);		//setup view for a specific cam
	virtual void SetupMatrices(LPDIRECT3DDEVICE9);		//setup origin matrix
	virtual void SetupLight(LPDIRECT3DDEVICE9);			//setup light

	virtual void InvalidateObjects();					//release drawable objects to free space 

	virtual bool CreateTerrainWithTexture(std::string map, std::string texture); 

	virtual void SetupSkybox(LPDIRECT3DDEVICE9);		
	virtual void SetupTerrain(LPDIRECT3DDEVICE9);
	
	virtual void CreateEntityWithMesh(D3DXVECTOR3, D3DXVECTOR3, Resource*);

	virtual void AddCamera(int, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, HWND*, InputHandler*);
	virtual Camera* GetCamera(int cam);

	virtual void AddEntity(Entity*);
	virtual Entity* GetEntity(uint32_t);

	virtual void MoveTerrainTo(D3DXVECTOR3, D3DXVECTOR3);

	virtual void RemoveEntity(uint32_t);
	virtual void MoveEntityTo(uint32_t, D3DXVECTOR3, D3DXVECTOR3);
	
private:
	uint32_t id;
	std::string name;

	virtual std::string CurrentDirectory(std::string);

private:
	Transform originTransform;

	Terrain* terrain;
	Skybox* skybox;


	std::map<int, Camera*> cameras;
	std::map<uint32_t, Entity*> entities;

	


};

#endif // SCENE_H_