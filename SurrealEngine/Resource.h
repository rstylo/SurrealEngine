#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <Windows.h>
#include <string>
#include <cstdint>
#include <d3dx9.h>

class Resource
{
public:
	Resource();

	virtual ~Resource();

	virtual bool Init(LPDIRECT3DDEVICE9) = 0;
	virtual void Draw(LPDIRECT3DDEVICE9) = 0;
	virtual uint32_t GetId();
	
protected:
	uint32_t id;


	
	
};

#endif // !RESOURCE_H_

