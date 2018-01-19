/*! \file  Object.h
\brief an extention of inputhandler that hold and gets keyboard inputs
*/

#ifndef OBJECT_H_
#define OBJECT_H_

#include <d3dx9.h>
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
	virtual void CleanUp();

	

private:
	std::string objectName;

	std::string textureName;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;

	LPDIRECT3DTEXTURE9 texture;

	bool initialised;

	int primCount;
	int vertexCount;
};

#endif // !OBJECT_H_