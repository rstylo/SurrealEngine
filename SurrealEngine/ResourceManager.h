#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <windows.h>						//voor unique ids
#include <map>
#include <d3dx9.h>
#include <cstdint>

class Resource;

class ResourceManager
{
public:
	ResourceManager(LPDIRECT3DDEVICE9*);
	virtual ~ResourceManager();
	virtual void Update();
	virtual void Draw();

	virtual void AddResource(Resource*);

	virtual Resource* GetResource(uint32_t);


	std::map<uint32_t, Resource*> resources;


	LPDIRECT3DDEVICE9* device;


};

#endif // !RESOURCEMANAGER_H_
