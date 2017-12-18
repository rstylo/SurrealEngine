#include "Resource.h"



Resource::Resource()
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

void Resource::Create(std::string)
{
	//overload in mesh and texture
}

void Resource::Draw()
{

}
