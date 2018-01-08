#include "ResourceManager.h"
#include "Resource.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (auto it = resources.begin(); it != resources.end(); it++)
	{
		delete it->second;
	}

	resources.clear();

}

void ResourceManager::AddResource(Resource* _resource) 
{
	if(resources.find(_resource->GetId()) != resources.end()) return;
		resources[_resource->GetId()] = _resource;

}

Resource* ResourceManager::GetResource(uint32_t _uuid)
{
	if (resources.find(_uuid) != resources.end())
		return resources.find(_uuid)->second;

	return NULL;
}