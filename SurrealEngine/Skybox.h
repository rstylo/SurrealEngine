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

	virtual bool Init(Renderer*);						//! Makes the renderer load a texture and create a cube with texturecoordinates 
														//! to correctly fit a skyboxtype of texture.
	
	virtual void Invalidate(Renderer*);					//! Releases texture data and vertex/index buffers on the renderer to free space
	
	virtual void SetupMatrices(Renderer*, Transform);	//! Places the correct rotation on the skybox from the camera's point of view

	virtual void Draw(Renderer*);						//! Makes the renderer draw the cube and the texture created by the Init function

	virtual void SetTexture(std::string);				//! Sets the texturepath of the skybox
	virtual std::string GetTexture();					//! Returns the texturepath of the skybox

private:
	std::string textureName;				//! The path of the skyboxtexture

	Transform transform;					//! The transformation values of the skybox

	uint32_t id;							//! The unique identifier of the skybox
};

#endif // !SKYBOX_H_