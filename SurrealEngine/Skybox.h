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
	Skybox();
	virtual ~Skybox();

	virtual bool Init(Renderer*);

	virtual void Update(Vector3);
	virtual void Create();
	virtual void Invalidate(Renderer*);


	virtual void SetupMatrices(Renderer*, Transform);

	virtual void Draw(Renderer*);

	virtual void SetTexture(std::string);
	virtual std::string GetTexture();

private:
	std::string textureName;

	Transform transform;

	Vector3 middle;

	//Logger logger;

	uint32_t id;
};

#endif // !SKYBOX_H_