/*
* Class: Entity.h
* Description: This class is used for reading and calling commands. It can als be use to print text on to the console
* Note : Class is as of now reliant to sceneManager
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <d3dx9.h>							//d3dx variabelen en calls
#include <Windows.h>						//null pointer
#include <cstdint>							//voor uint32_t
#include <list>
#include <string>

#include "Transform.h"
#define _USE_MATH_DEFINES

class Resource;
class Mesh;

class Entity
{
public:
	Entity(Vector3, Vector3);							//starting position and rotation
	virtual ~Entity();

	virtual void SetupMatrices(Renderer*, Transform);				//sets the world transform of this entity
	virtual void Draw(Renderer*);						//draws the resources this entity has
	

	virtual void AddResource(Resource*);						//add resource to the to be draw resources
	virtual bool Init(Renderer*);						

	virtual uint32_t GetId();									//used to indetify the entity

	Transform transform;

private:

	uint32_t id;												//voor unique ids

	std::list<Resource*> myResources;							//to be drawn resources
	
};

#endif // !ENTITY_H_