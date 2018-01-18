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
#include "Renderer.h"

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

	virtual bool InitEntities(Renderer*);
	virtual void Draw(Renderer*);
	virtual void Update();

	virtual void SetupView(Renderer*, int);		//setup view for a specific cam
	virtual void SetupMatrices(Renderer*, int);		//setup origin matrix
	virtual void SetupLight(Renderer*);			//setup light

	virtual void InvalidateObjects();					//release drawable objects to free space 

	virtual bool CreateTerrainWithTexture(std::string map, std::string texture); 
	virtual bool SetSkyboxTexture(std::string);

	virtual void SetupSkybox(Renderer*);
	virtual void SetupTerrain(Renderer*);
	
	virtual void CreateEntityWithMesh(Vector3, Vector3, Resource*);

	virtual void AddCamera(int, Vector3, Vector3, HWND*, InputHandler*);
	virtual Camera* GetCamera(int cam);

	virtual void AddEntity(Entity*);
	virtual Entity* GetEntity(uint32_t);

	virtual void SetCameraHeightMap();

	virtual void MoveTerrainTo(Vector3, Vector3);

	virtual void RemoveEntity(uint32_t);
	virtual void MoveEntityTo(uint32_t, Vector3, Vector3);
	
	virtual std::string GetSceneInfo();

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