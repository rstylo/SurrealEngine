#include "Resource.h"
#include "Sprite.h"



Resource::Resource(std::string _resourceType)
	:resourceType(_resourceType)	//nodig om te zien in de base klassse welke type de childklasse is
{
	//uuid aanmaken
	id = reinterpret_cast<uint32_t>(this);
}


Resource::~Resource()
{

}

uint32_t Resource::GetId()
{
	return id;
}

