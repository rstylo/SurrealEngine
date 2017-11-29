#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <Windows.h>
#include <string>
#include <cstdint>

class Resource
{
public:
	Resource(std::string);

	virtual ~Resource();

	uint32_t GetId();
	
protected:
	uint32_t id;

	std::string resourceType;


	
	
};

#endif // !RESOURCE_H_

