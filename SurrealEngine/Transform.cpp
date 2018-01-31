#include "Transform.h"
#include "DirectXRenderer.h"

Transform::Transform()
{
	//! initialize position, rotation, scale vectors
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);

}


Transform::~Transform()
{
}

void Transform::SetupMatrices(Renderer* renderer)
{
	//! transforms world matrix
	if (renderer != NULL)
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->SetupMatrices(position, rotation);
		}
}

void Transform::SetupMatrices(Renderer* renderer, Transform origin)
{

	if (renderer != NULL)
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->SetupMatrices(position, rotation, origin.GetPosition(), origin.GetRotation());
		}
}

void Transform::SetupMatricesRotate(Renderer* renderer, Vector3 _rotation)
{
	//! setup matrice with only a given rotation
	if (renderer != NULL)
		if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer))
		{
			dxrenderer->SetupMatricesRotate(position);
		}
}

Vector3 Transform::GetPosition()
{
	//! returns current postion vector
	return position;
}

void Transform::SetPosition(Vector3 _position)
{
	//! sets position vector to given vector
	position = _position;
}

Vector3 Transform::GetRotation()
{
	//! returns rotation vector
	return rotation;
}

void Transform::SetRotation(Vector3 _rotation)
{
	//! sets rotation vector
	rotation = _rotation;
}

Vector3 Transform::GetScale()
{

	//! returns the scale vector
	return scale;
}

void Transform::SetScale(Vector3 _scale)
{
	//! sets tje scale vector
	scale = _scale;
}