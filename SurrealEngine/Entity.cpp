#include "Entity.h"


Entity::Entity(float x, float y, float z)
{
	id = reinterpret_cast<uint32_t>(this);			//cast de classe naar een uint32_t, sinds klassen al unique zijn zal dit ervoor zorgen dat elke entity een eigen positive int getal als id heeft

	position.x = x;
	position.y = y;
	position.z = z;
}


Entity::~Entity()
{
}

void Entity::Draw()									//de entity draw functie draw all zijn resources in plaatst van dit via de resource manager te doen
{

}

uint32_t Entity::GetId()							
{
	return id;														
}