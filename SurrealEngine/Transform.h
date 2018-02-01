/*! \file  Transform.h
	\brief this class is used to move drawable objects around in the world
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Renderer.h"

class Transform
{
public:
	Transform();
	virtual ~Transform();

	virtual void SetupMatrices(Renderer*);
	virtual void SetupMatrices(Renderer*, Transform);
	virtual void SetupMatricesRotate(Renderer*, Vector3);

	virtual Vector3 GetPosition();
	virtual void SetPosition(Vector3);

	virtual Vector3 GetRotation();
	virtual void SetRotation(Vector3);

	virtual Vector3 GetScale();
	virtual void SetScale(Vector3);

private:

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

};

#endif // TRANSFORM_H_