#include "Resource.h"



Resource::Resource()
{
	//! initialise with unique id
	id = reinterpret_cast<uint32_t>(this);
}


Resource::~Resource()
{

}

uint32_t Resource::GetId()
{
	return id;
}

void Resource::Invalidate()
{
	CleanUp();
}
