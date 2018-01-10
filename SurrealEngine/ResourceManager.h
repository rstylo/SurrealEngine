#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>

#include <cstdint>

class Resource;
class Mesh;

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();
	virtual bool AddResource(Resource*);

	virtual Resource* GetResource(uint32_t);

	virtual Resource* GetMesh(std::string);
	virtual Resource* CreateMesh(std::string);



private:

	
	std::map<uint32_t, Resource*> resources;
	std::map<std::string, uint32_t> meshes;


};

#endif // !RESOURCEMANAGER_H_
