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

	virtual void Draw() = 0;
	virtual uint32_t GetId();
	virtual void Create(std::string);
	
protected:
	uint32_t id;


	
	
};

#endif // !RESOURCE_H_

