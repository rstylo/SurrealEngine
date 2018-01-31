/*! \file  Transform.h
	\brief this class is used to move drawable objects around in the world
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_



struct Vector3 {
	float x, y, z;
	Vector3() {};
	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	};
};


class Renderer;

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