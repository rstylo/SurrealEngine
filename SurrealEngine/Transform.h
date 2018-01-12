/*
* Class: Transform.h
* Description : this class stores the position and rotation of world objects. And setup world matrices for other classes to use
* Note :
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <d3dx9.h>
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

class Transform
{
public:
	Transform();
	virtual ~Transform();


	virtual void SetupMatrices(LPDIRECT3DDEVICE9);

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