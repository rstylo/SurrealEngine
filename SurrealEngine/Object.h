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
	Object(std::string);				//! intiliase with objects name
	virtual ~Object();

	virtual bool Init(Renderer*);		//! intialise object
	virtual void Draw(Renderer*);		//! draw object

	virtual void SetTexture(std::string);	//! set new texture to be drawn on the object
	
	virtual std::string GetObjectName();	//! returns object name
	virtual void CleanUp(Renderer*);

	

private:
	std::string objectName;

	std::string textureName;

	bool initialised;

	uint32_t id;
};

#endif // !OBJECT_H_