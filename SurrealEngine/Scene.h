/*! \file  Scene.h
	\brief is the a class that draws all active objects that form the world
*/

#ifndef SCENE_H_
#define SCENE_H_


#include <cstdint>							
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

	virtual void SetupView(Renderer*, int);				//! setup view for a specific cam
	virtual void SetupMatrices(Renderer*, int);			//! setup origin matrix
	virtual void SetupLight(Renderer*);					//! setup light

	virtual void InvalidateObjects(Renderer*);					//! release drawable objects to free space 

	virtual bool CreateTerrainWithTexture(std::string map, std::string texture);	//! create(/change if already existing) a terrain with a heightmap and a texture
	virtual bool CreateSkyboxWithTexture(std::string texture);						//! create(/change if already existing change)  a skybox with a texture

	virtual void SetupSkybox(Renderer*);
	virtual void SetupTerrain(Renderer*);

	virtual void CreateEntityWithResource(Vector3, Vector3, Resource*);				//! create an entity with a mesh
	

	virtual void AddCamera(int, Vector3, Vector3, HWND*, InputHandler*);			//! create a camera on a certain position with an id#
	virtual Camera* GetCamera(int cam);												//! get a pointer to a specific already existing camera object

	virtual void AddEntity(Entity*);												
	virtual Entity* GetEntity(uint32_t);

	virtual void MoveTerrainTo(Vector3, Vector3);

	virtual void RemoveEntity(uint32_t);											//! delete a entity
	virtual void MoveEntityTo(uint32_t, Vector3, Vector3);							//! move a entity to a position and rotate it

	virtual void SetCameraHeightMap();												//! 
	
	
	virtual std::string GetSceneInfo();												//! returns a string of all information about entities, resources, skyboxes and terrains in this scene

private:
	uint32_t id;																	//! unique id of this scene
	std::string name;																//! name of this scene

	virtual std::string CurrentDirectory(std::string);								//! returns current working directory

private:
	Transform originTransform;

	Terrain* terrain;																
	Skybox* skybox;


	std::map<int, Camera*> cameras;													//! holds camera with a int as indentifier
	std::map<uint32_t, Entity*> entities;											//! holds pointers to all entities in this scene with there identifier


};

#endif // SCENE_H_