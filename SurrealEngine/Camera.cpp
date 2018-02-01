#include "Camera.h"
#include "InputHandler.h"


Camera::Camera(Vector3 _rotation, Vector3 _translation, HWND* _hwnd, InputHandler* _inputHandler)
{
	cameraHeight = 0;

	lookingAt = false;

	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;

	position.x = _translation.x;
	position.y = _translation.y;
	position.z = _translation.z;

	hwnd = _hwnd;
	inputHandler = _inputHandler;			
}


Camera::~Camera()
{
}

void Camera::SetupView(Renderer* renderer)
{
	//! setup view matrix
	if (renderer != NULL)
		renderer->SetupView(1, 1000);
}

void Camera::SetLookAt(bool state)
{
	//! set position camera should look at
	lookingAt = state;
}

void Camera::Update()
{

	//! get input and move/rotate accordingly the camera depending
	if (*hwnd == GetFocus()) {
		if (inputHandler->CheckKeyboardPressed('w')) {
			if (inputHandler->CheckKeyboardPressed('a')) {
				MoveTo(rotation.y + (0.25 * pi));
			}
			else if (inputHandler->CheckKeyboardPressed('d')) {
				MoveTo(rotation.y - (0.25 * pi));
			}
			else {
				MoveForwards();
			}
		}
		else if (inputHandler->CheckKeyboardPressed('s')) {
			if (inputHandler->CheckKeyboardPressed('a')) {
				MoveTo(rotation.y + (0.75 * pi));
			}
			else if (inputHandler->CheckKeyboardPressed('d')) {
				MoveTo(rotation.y - (0.75 * pi));
			}
			else {
				MoveBackwards();
			}
		}
		else {
			if (inputHandler->CheckKeyboardPressed('a')) {
				MoveLeft();
			}
			if (inputHandler->CheckKeyboardPressed('d')) {
				MoveRight();
			}
		}

		if (inputHandler->CheckKeyboardPressed('.')) {
			MoveUp();
		}
		if (inputHandler->CheckKeyboardPressed('c')) {
			MoveDown();
		}
		if (inputHandler->CheckKeyboardPressed('e')) {
			Rotate(1, 0);
		}
		if (inputHandler->CheckKeyboardPressed('q')) {
			Rotate(-1, 0);
		}

		if (heightData != NULL && depth != NULL) {
			if (-position.x > 0 && -position.x < width && -position.z > 0 && -position.z < depth) {
				if (position.y > -heightData[(int)-position.x * depth + (int)-position.z] - 5)
					position.y = -heightData[(int)-position.x * depth + (int)-position.z] - 5;
			}
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
	//! move to a position relative to the camera current position using radians
	float speed = 0.25;
	position.z -= cos(rot)*speed;
	position.x += sin(rot)*speed;
}

void Camera::Rotate(float x, float y)
{
	//! rotate the camera depending on a x andy position, generally from a mouse
	float speed = 2;
	rotation.x -= speed*y / 100;
	rotation.y -= speed*x / 100;
}

void Camera::MoveLeft()
{
	float rotLeft = rotation.y + (0.5 * pi);
	MoveTo(rotLeft);
}

void Camera::MoveRight()
{
	float rotRight = rotation.y - (0.5 * pi);
	MoveTo(rotRight);
}

void Camera::MoveForwards()
{
	float rotForward = rotation.y;
	MoveTo(rotForward);
}

void Camera::MoveBackwards()
{
	float rotBack = rotation.y + pi;
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

void Camera::SetHeight(byte* _heightData, int _depth, int _width)
{
	heightData = _heightData;
	depth = _depth;
	width = _width;
}

Vector3 Camera::GetPosition() {
	return position;
}

Vector3 Camera::GetRotation() {
	return rotation;
}