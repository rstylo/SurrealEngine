/*
* Class: Resource.h
* Description : base class from which resource type classes can inherit from
* Note : 
*/

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
	virtual uint32_t GetId();						//needs a identifacation number, despite being any other derived version of this class,
	
protected:
	uint32_t id;


	
	
};

#endif // !RESOURCE_H_

