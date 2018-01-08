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
class Mesh;

class Entity
{
public:
	Entity(D3DXVECTOR3, D3DXVECTOR3);
	virtual ~Entity();

	virtual void SetupMatrices(LPDIRECT3DDEVICE9);
	virtual void Draw(LPDIRECT3DDEVICE9);
	

	virtual void AddResource(Resource*);
	virtual bool Init(LPDIRECT3DDEVICE9);

	virtual uint32_t GetId();

private:

	uint32_t id;												//voor unique ids

	std::list<Resource*> myResources;	

	Object* my3dObject;

	D3DXVECTOR3 position;										//ELKE entity moet een positie in de wereld hebben
	D3DXVECTOR3 rotation;


};

#endif // !ENTITY_H_