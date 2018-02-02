/*! \file  Skybox.h
	\brief this class is used to draw and move the skybox texture
*/

#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <string>
#include "Transform.h"


class Skybox
{
public:
	Skybox();												//! skybox constructor
	virtual ~Skybox();

	virtual bool Init(Renderer*);							//! initialise with generic renderer

	virtual void Update(Vector3);							//! update skyboxes starting position								
	virtual void Invalidate(Renderer*);						//! cleanup rendering objects to free space


	virtual void SetupMatrices(Renderer*, Transform);		//! setup position relative to a given transform

	virtual void Draw(Renderer*);							//! draw the skybox into given renderer

	virtual void SetTexture(std::string);				 //! sets skybox's texture
	virtual std::string GetTexture();					//! returns current texture name

private:
	std::string textureName;

	Transform transform;

	Vector3 middle;

	//Logger logger;

	uint32_t id;
};

#endif // !SKYBOX_H_