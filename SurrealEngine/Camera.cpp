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

	translation.x = _translation.x;
	translation.y = _translation.y;
	translation.z = _translation.z;

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

	D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);
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

void Camera::Update(int _window)
{
	inputHandler->Update(this,_window);
	GetMouse(_window);
	GetKeyPressed(_window);
}

void Camera::MoveTo(D3DXVECTOR3)
{

}

void Camera::Rotate(float x, float y)
{
	rotation.y -= y*2*D3DX_PI/100;	
	rotation.z += 0.1f*x*cos(rotation.y);
	rotation.x += 0.1f*x*sin(rotation.y);
}

void Camera::MoveLeft()
{
	float speed = 3.0f;
	translation.z -= speed*cos(rotation.y+0.5*D3DX_PI);
	translation.x += speed*sin(rotation.y+ 0.5*D3DX_PI);
}

void Camera::MoveRight()
{
	float speed = 3.0f;
	translation.z -= speed*cos(rotation.y - 0.5*D3DX_PI);
	translation.x += speed*sin(rotation.y - 0.5*D3DX_PI);
}

void Camera::MoveForwards()
{
	float speed = 3.0f;
	translation.z -= speed*cos(rotation.y);
	translation.x += speed*sin(rotation.y);
}

void Camera::MoveBackwards()
{
	float speed = 3.0f;
	translation.z += speed*cos(rotation.y);
	translation.x -= speed*sin(rotation.y);
}

void Camera::MoveUp()
{
	translation.y -= 2.0f;
}

void Camera::MoveDown()
{
	translation.y += 2.0f;
}

void Camera::GetKeyPressed()
{
	if (inputHandler->HandleKeys('A')) {

	}

	if (keybuffer[wndn][DIK_A] & 0x80)
		cam->MoveLeft();
	if (keybuffer[wndn][DIK_W] & 0x80)
		cam->MoveForwards();
	if (keybuffer[wndn][DIK_S] & 0x80)
		cam->MoveBackwards();
	if (keybuffer[wndn][DIK_D] & 0x80)
		cam->MoveRight();
	if (keybuffer[wndn][DIK_C] & 0x80)
		cam->MoveDown();

	if (keybuffer[wndn][DIK_UP] & 0x80)
		cam->MoveForwards();
	if (keybuffer[wndn][DIK_LEFT] & 0x80)
		cam->MoveLeft();
	if (keybuffer[wndn][DIK_RIGHT] & 0x80)
		cam->MoveRight();
	if (keybuffer[wndn][DIK_DOWN] & 0x80)
		cam->MoveBackwards();

	if (keybuffer[wndn][DIK_SPACE] & 0x80)
		cam->MoveUp();

	if (keybuffer[wndn][DIK_U] & 0x80)

		if (keybuffer[wndn][DIK_ESCAPE] & 0x80)
			exit(0);
}

void Camera::GetMouse(int _wndn)
{
	MouseValues* test = inputHandler->Checkmouse(_wndn);
	Rotate(0, mouseValues[wndn]->dX);
	if (mouseValues[wndn]->button0)
		cam->MoveForwards();
}
