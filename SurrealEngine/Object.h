/*! \file  Object.h
\brief an extention of inputhandler that hold and gets keyboard inputs
*/

#ifndef OBJECT_H_
#define OBJECT_H_

#include <list>
#include <string>
#include "Resource.h"

#define FVF_VERTEXSTRUCTURE (D3DFVF_XYZ|D3DFVF_TEX1) //! flexible vertex format



class Renderer;

class Object : public Resource
{
public:
	Object(std::string);
	virtual ~Object();

	virtual bool Init(Renderer*);		//! intialise object
	virtual void Draw(Renderer*);		

	virtual void SetTexture(std::string);
	
	virtual std::string GetObjectName();
	virtual void CleanUp(Renderer*);

	

private:
	std::string objectName;

	std::string textureName;

	bool initialised;

	int primCount;
	int vertexCount;

	uint32_t id;
};

#endif // !OBJECT_H_