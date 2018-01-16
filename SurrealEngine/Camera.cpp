#include "Camera.h"
#include "InputHandler.h"
#include "DirectXRenderer.h"

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

void Camera::SetupView(Renderer* renderer)
{
	if (DirectXRenderer* dxrenderer = dynamic_cast<DirectXRenderer*>(renderer)) {
		LPDIRECT3DDEVICE9 _device = *dxrenderer->GetDevice();
		/*
		D3DXMATRIX worldMtrx;
		D3DXMatrixIdentity(&worldMtrx);

		D3DXMATRIXA16 trans;

		D3DXMatrixTranslation(&trans, position.x, position.y, position.z);

		D3DXMATRIXA16 rotX;
		D3DXMATRIXA16 rotY;
		D3DXMATRIXA16 rotZ;

		D3DXMatrixRotationX(&rotX, rotation.x);
		D3DXMatrixRotationY(&rotY, rotation.y);
		D3DXMatrixRotationZ(&rotZ, rotation.z);

		worldMtrx = trans*rotX * rotY * rotZ;

		_device->SetTransform(D3DTS_WORLD, &worldMtrx);
		
		//set eye position
		if (lookingAt == true)
		{
			eye = position;
			eye.y + 5;


			//setlook AT to foward from the current position
			lookAt = position;
			lookAt.y += cameraHeight;
			lookAt.z -= cos(rotation.y);
			lookAt.x += sin(rotation.y);


			//create viematrix looking at lookat position
			D3DXMATRIX viewMtrx;

			D3DXMatrixLookAtLH(&viewMtrx, &eye, &lookAt, &up);

			_device->SetTransform(D3DTS_VIEW, &viewMtrx);
		}
		*/
		//create porjection matrix with 0.25PI as the view direction in y, 1 unit from the view as near viewplane and 1000 as far viewplane
		D3DXMATRIX projectionMtrx;
		D3DXMatrixPerspectiveFovLH(&projectionMtrx, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
		_device->SetTransform(D3DTS_PROJECTION, &projectionMtrx);
	}
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
			Rotate(0, 1);
		}
		if (inputHandler->CheckKeyboardPressed('q')) {
			Rotate(0, -1);
		}
		Rotate(inputHandler->CheckMouseValues('x'), inputHandler->CheckMouseValues('y'));

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
	rotation.x -= speed*y / 100;
	rotation.y -= speed*x / 100;
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
	position.y -= 0.5f;

}

void Camera::MoveDown()
{
	position.y += 0.5f;
}

D3DXVECTOR3 Camera::GetPosition() {
	return position;
}

D3DXVECTOR3 Camera::GetRotation() {
	return rotation;
}