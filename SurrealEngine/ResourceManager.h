/*
* Class: ResourceManager.h
* Description : This class manages resources and any derived versions of it. This class stores resources and deletes them when program stops
* Note :
*/

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
	virtual Resource* CreateMesh(std::string); //create a mesh with a certain name, returns created mesh or already existing one

private:

	
	std::map<uint32_t, Resource*> resources;
	std::map<std::string, uint32_t> meshes;


};

#endif // !RESOURCEMANAGER_H_
