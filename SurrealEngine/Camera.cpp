#include "Camera.h"
#include "InputHandler.h"

Camera::Camera(D3DXVECTOR3 _eye, D3DXVECTOR3 _lookAt, D3DXVECTOR3 _rotation, D3DXVECTOR3 _translation, InputHandler* _inputHandler)
{
	float twoPi = D3DX_PI; //handig om een eigen util/math klasse te maken waar twopi al in is gedefineerd

	eye.x = _eye.x;
	eye.y = _eye.y;
	eye.z = _eye.z;

	lookAt.x = _lookAt.x;
	lookAt.y = _lookAt.y;
	lookAt.z = _lookAt.z;

	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;

	position.x = _translation.x;
	position.y = _translation.y;
	position.z = _translation.z;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	inputHandler = _inputHandler;
}


Camera::~Camera()
{
}

void Camera::SetupView(LPDIRECT3DDEVICE9 _device)
{
	D3DXMATRIXA16 trans;

	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
	D3DXMATRIX worldMtrx = trans;
	_device->SetTransform(D3DTS_WORLD, &worldMtrx);

	D3DXMATRIXA16 rotX;
	D3DXMATRIXA16 rotY;
	D3DXMATRIXA16 rotZ;

	D3DXMatrixRotationX(&rotX, rotation.x);
	D3DXMatrixRotationY(&rotY, rotation.y);
	D3DXMatrixRotationZ(&rotZ, rotation.z);

	worldMtrx *= rotX *rotY * rotZ;
	_device->SetTransform(D3DTS_WORLD, &worldMtrx);

	D3DXMATRIX viewMtrx;
	D3DXMatrixLookAtLH(&viewMtrx, &eye, &lookAt, &up);
	_device->SetTransform(D3DTS_VIEW, &viewMtrx);

	D3DXMATRIX projectionMtrx;
	D3DXMatrixPerspectiveFovLH(&projectionMtrx, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	_device->SetTransform(D3DTS_PROJECTION, &projectionMtrx);


}

void Camera::LookAt(D3DXVECTOR3 _lookAt)
{
	lookAt = _lookAt;
}

void Camera::Update()
{
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
	Rotate(0, inputHandler->CheckMouseValues('x'));

	if (inputHandler->CheckMousePressed(0)) {
	}
}

void Camera::MoveTo(D3DXVECTOR3)
{

}

void Camera::Rotate(float x, float y)
{
	rotation.y -= y*2*D3DX_PI/200;	
	rotation.z += 0.1f*x*cos(rotation.y);
	rotation.x += 0.1f*x*sin(rotation.y);
}

void Camera::MoveLeft()
{
	float speed = 1.0f;
	position.z -= speed*cos(rotation.y+0.5*D3DX_PI);
	position.x += speed*sin(rotation.y+ 0.5*D3DX_PI);
}

void Camera::MoveRight()
{
	float speed = 1.0f;
	position.z -= speed*cos(rotation.y - 0.5*D3DX_PI);
	position.x += speed*sin(rotation.y - 0.5*D3DX_PI);
}

void Camera::MoveForwards()
{
	float speed = 1.0f;
	position.z -= speed*cos(rotation.y);
	position.x += speed*sin(rotation.y);
}

void Camera::MoveBackwards()
{
	float speed = 1.0f;
	position.z += speed*cos(rotation.y);
	position.x -= speed*sin(rotation.y);
}

void Camera::MoveUp()
{
	position.y -= 2.0f;
}

void Camera::MoveDown()
{
	position.y += 2.0f;
}

