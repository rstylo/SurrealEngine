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

	virtual void SetupMatrices(Renderer*);					//! setups world matrix from own position, rotation and scale
	virtual void SetupMatrices(Renderer*, Transform);		//! setups world matrix relative to a other transform
	virtual void SetupMatricesRotate(Renderer*, Vector3);	//! setups world matrix with only a rotation 

	virtual Vector3 GetPosition();							//! returns vector3 to position
	virtual void SetPosition(Vector3);						//! set this transforms position

	virtual Vector3 GetRotation();						//! returns vector3 to rotation
	virtual void SetRotation(Vector3);					//! set this transforms rotation

	virtual Vector3 GetScale();						//! returns vector3 to scale
	virtual void SetScale(Vector3);					//! set this transforms scale

private:

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

};

#endif // TRANSFORM_H_