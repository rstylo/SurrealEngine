#include "Camera.h"
#include "InputHandler.h"

Camera::Camera(D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation, D3DXVECTOR3 _translation, HWND* _hwnd, InputHandler* _inputHandler)
{
	eye.x = _eye.x;
	eye.y = _eye.y;
	eye.z = _eye.z;

	lookAt.x = _lookAt.x;
	lookAt.y = _lookAt.y;
	lookAt.z = _lookAt.z;

	cameraHeight = 0;

	lookingAt = false;

	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;

	position.x = _translation.x;
	position.y = _translation.y;
	position.z = _translation.z;

	up.x = 0.0f;
	up.y = 1.0f;					
	up.z = 0.0f;

	hwnd = _hwnd;
	inputHandler = _inputHandler;			
}


Camera::~Camera()
{
}

void Camera::SetupView(LPDIRECT3DDEVICE9 _device)
{
	//set eye position
	eye = position;
	eye.y + 5;

	if (lookingAt == false)
	{
		lookAt = position;
		lookAt.y += cameraHeight;
		lookAt.z -= cos(rotation.y);
		lookAt.x += sin(rotation.y);
	}

	D3DXMATRIX viewMtrx;

	D3DXMatrixLookAtLH(&viewMtrx, &eye, &lookAt, &up);
	
	_device->SetTransform(D3DTS_VIEW, &viewMtrx);


	D3DXMATRIX projectionMtrx;
	D3DXMatrixPerspectiveFovLH(&projectionMtrx, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	_device->SetTransform(D3DTS_PROJECTION, &projectionMtrx);
	

}

void Camera::SetLookAt(bool state)
{
	lookingAt = state;
}
void Camera::LookAt(D3DXVECTOR3 _lookAt)
{
	lookAt = _lookAt;
}

void Camera::Update()
{
	if (*hwnd == GetFocus()) {
		Rotate(0, inputHandler->CheckMouseValues('x'));

		if (inputHandler->CheckKeyboardPressed('a')) {
			MoveLeft();
		}
		if (inputHandler->CheckKeyboardPressed('s')) {
			MoveBackwards();
		}
		if (inputHandler->CheckKeyboardPressed('d')) {
			MoveRight();
		}
		if (inputHandler->CheckKeyboardPressed('w')) {
			MoveForwards();
		}
		if (inputHandler->CheckKeyboardPressed('.')) {
			MoveUp();
		}
		if (inputHandler->CheckKeyboardPressed('c')) {
			MoveDown();
		}
		if (inputHandler->CheckKeyboardPressed('e')) {
			Rotate(0, rotation.y);
		}
		if (inputHandler->CheckKeyboardPressed('q')) {
			Rotate(0, rotation.y);
		}
		Rotate(inputHandler->CheckMouseValues('y'), inputHandler->CheckMouseValues('x'));

		if (inputHandler->CheckMousePressed(0)) {
			
		}

		if (inputHandler->CheckMousePressed(1)) {
			
		}
	}
}

void Camera::MoveTo(float rot)
{
	float speed = 0.5;
	position.z -= 0.5*cos(rot)*speed;
	position.x += 0.5*sin(rot)*speed;
}

void Camera::Rotate(float x, float y)
{
	float speed = 2;
	rotation.y -= speed*y * 2 * D3DX_PI / 1000;
	cameraHeight -= 0.05*x;
}

void Camera::MoveLeft()
{
	float rotLeft = rotation.y + (0.5 * D3DX_PI);
	MoveTo(rotLeft);

}

void Camera::MoveRight()
{
	float rotRight = rotation.y - (0.5 * D3DX_PI);
	MoveTo(rotRight);
}

void Camera::MoveForwards()
{
	float rotForward = rotation.y;
	MoveTo(rotForward);
}

void Camera::MoveBackwards()
{
	float rotBack = rotation.y + D3DX_PI;
	MoveTo(rotBack);
}

void Camera::MoveUp()
{
	position.y += 0.5f;

}

void Camera::MoveDown()
{
	position.y -= 0.5f;
}

D3DXVECTOR3 Camera::GetPosition() {
	return position;
}