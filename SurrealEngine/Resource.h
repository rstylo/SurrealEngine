/*! \file  Resource.h
	\brief identifies and holds meshes and objects 
*/

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <cstdint>
#include "Renderer.h"

class Resource
{
public:
	Resource();

	virtual ~Resource();

	virtual bool Init(Renderer*) = 0;
	virtual void Draw(Renderer*) = 0;

	virtual void CleanUp(Renderer*) = 0;


	virtual uint32_t GetId();						//needs a identifacation number, despite being any other derived version of this class,
	virtual void Invalidate(Renderer*);
	
protected:
	uint32_t id;


	
	
};

#endif // !RESOURCE_H_

