#include "Entity.h"
//#include "Resource.h"
#include "Sprite.h"



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
	if (sprite != NULL)
	{
		sprite->Draw(position);							
	}
}

void Entity::AddSprite(Sprite* _sprite)				//AddResource is mishien beter?, nogmals sprite is hier meer een test
{
	if (sprite != NULL) {
		delete sprite;
		sprite = NULL;
	}

	sprite = _sprite;
}

uint32_t Entity::GetId()							
{
	return id;														
}