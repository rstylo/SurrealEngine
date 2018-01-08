#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>

#include <cstdint>

class Resource;

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();
	virtual void AddResource(Resource*);

	virtual Resource* GetResource(uint32_t);

private:

	std::map<uint32_t, Resource*> resources;


};

#endif // !RESOURCEMANAGER_H_
