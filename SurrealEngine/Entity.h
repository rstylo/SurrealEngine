#ifndef ENTITY_H_
#define ENTITY_H_

#include <d3dx9.h>							//d3dx variabelen en calls
#include <Windows.h>						//null pointer
#include <cstdint>							//voor uint32_t
#include <list>
#include <string>

#define _USE_MATH_DEFINES

class Resource;
class Object;
class Rectangle;

class Entity
{
public:
	Entity(float, float, float);
	virtual ~Entity();

	virtual void Draw(LPDIRECT3DDEVICE9);
	virtual void AddResource(Resource*);


	virtual void Update();
	virtual uint32_t GetId();

private:

	uint32_t id;												//voor unique ids

	std::list<Resource*> myResources;	

	Object* my3dObject;

	D3DXVECTOR3 position;										//ELKE entity moet een positie in de wereld hebben


};

#endif // !ENTITY_H_