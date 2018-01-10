#include "ResourceManager.h"
#include "Resource.h"
#include "Mesh.h"
#include "Texture.h"


ResourceManager::ResourceManager(LPDIRECT3DDEVICE9* _device)
{
	device = _device;

	//make a test mesh
	testMesh = new Mesh(device);
	testMesh->Create("tiger.x");

	//make a test texture
	testTexture = new Texture(device);
	testTexture->Create("tiger.bmp");

	AddResource(testMesh);
	AddResource(testTexture);
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


void ResourceManager::Update() 
{

}


//deze func wordt niet aangeroepen
void ResourceManager::Draw()
{
	testMesh->Draw();
	testTexture->Draw();



}