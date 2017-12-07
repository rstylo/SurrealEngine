#ifndef ENTITY_H_
#define ENTITY_H_

#include <d3dx9.h>							//d3dx variabelen en calls
#include <Windows.h>						//null pointer
#include <cstdint>							//voor uint32_t

#define _USE_MATH_DEFINES

class Sprite;

class Entity
{
public:
	Entity(float, float, float);
	virtual ~Entity();

	virtual void Draw();
	virtual uint32_t GetId();

private:
	uint32_t id;							//voor unique ids
	D3DXVECTOR3 position;					//ELKE entity moet een positie in de wereld hebben
};

#endif // !ENTITY_H_