/*! \file  ResourceManager.h
	\brief creates and deletes resources
*/


#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>

#include <cstdint>

class Resource;
class Mesh;
class Object;

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();
	virtual bool AddResource(Resource*);				

	virtual Resource* GetResource(uint32_t);

	virtual Resource* GetMesh(std::string);		
	virtual Resource* CreateMesh(std::string); //! create a mesh with a certain name, returns created mesh or already existing one

	virtual Resource* GetObj(std::string);	 
	virtual Resource* CreateObj(std::string); //! create an object with a certain name, returns created object or already existing one

private:

	
	std::map<uint32_t, Resource*> resources;		//! holds all pointers to resources in the scene
	std::map<std::string, uint32_t> meshes;			//! holds id's to meshes
	std::map<std::string, uint32_t> objects;		//! holds id's to objects

};

#endif // !RESOURCEMANAGER_H_
