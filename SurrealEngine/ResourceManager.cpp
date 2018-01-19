#include "ResourceManager.h"
#include "Resource.h"
#include "Mesh.h"
#include "Object.h"

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	//! deletes all resources
	for (auto it = resources.begin(); it != resources.end(); it++)
	{
		delete it->second;
	}

	resources.clear();
	meshes.clear();

}

bool ResourceManager::AddResource(Resource* _resource) 
{
	//!this function returns false when a resource already exists, so u can use GetResource/GetMesh to avoid having duplicates


	//! checks if resource already exists
	if(resources.find(_resource->GetId()) != resources.end())
		return false;

	//! checks if the resource a mesh?
	if (Mesh* isMesh = dynamic_cast<Mesh*>(_resource))
	{
		//! check if mesh with the same name already exists
		if (meshes.find(isMesh->GetMeshName()) != meshes.end())
			return false;

		//! register the meshName
		meshes[isMesh->GetMeshName()] = isMesh->GetId();
	}

	//! is the resource an object?
	if (Object* isObject = dynamic_cast<Object*>(_resource))
	{
		//! check if mesh with the same name already exists
		if (objects.find(isObject->GetObjectName()) != objects.end())
			return false;

		//! register the meshName
		objects[isObject->GetObjectName()] = isObject->GetId();
	}

	//! Add the resource
	resources[_resource->GetId()] = _resource;
	return true;
}

Resource* ResourceManager::GetResource(uint32_t _uuid)
{
	//! returns resource with given unique identifier
	if (resources.find(_uuid) != resources.end())
		return resources.find(_uuid)->second;

	return NULL;
}

Resource* ResourceManager::GetMesh(std::string meshName)
{
	//! return mesh with meshe's name as identifier
	if (meshes.find(meshName) != meshes.end())
		return resources.find(meshes.find(meshName)->second)->second;

	return NULL;

	

}

Resource* ResourceManager::CreateMesh(std::string meshName)
{
	//! returns created mesh or already existing one with the same name
	if (GetMesh(meshName) != NULL)
	{
		return GetMesh(meshName);
	}

	Resource* mesh = new Mesh(meshName);
	AddResource(mesh);
	
	return mesh;
}


Resource * ResourceManager::GetObj(std::string objectName)
{
	//! return object with object's name as identifier
	if (objects.find(objectName) != objects.end())
		return resources.find(objects.find(objectName)->second)->second;

	return NULL;
}

Resource * ResourceManager::CreateObj(std::string objName)
{
	//! returns a created object resource or already existing one with the same name
	if (GetObj(objName) != NULL)
	{
		return GetObj(objName);
	}

	Resource* object = new Object(objName);
	AddResource(object);

	return object;
}
