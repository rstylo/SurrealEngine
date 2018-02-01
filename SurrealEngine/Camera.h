/*! \file Camera.h
	\brief This class is used for setting up the view matrix of the current scene
*/
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Renderer.h"
#include "InputHandler.h"

const float pi = 3.141592654f;

class Camera
{
public:
	Camera(Vector3, Vector3, HWND*, InputHandler*);				//HWND with the window in which the view is to be displayed and a inputhandler from witch it can get real time input
	virtual ~Camera();

	virtual void SetupView(Renderer*);							//rendering routine

	virtual void SetLookAt(bool);

	virtual void Update();										//main routine, used for moving and rotating the view matrix

	virtual void MoveTo(float);									//move the camera towards a certain angle
	virtual void Rotate(float, float);							//rotate transform pitch and yaw

	virtual void MoveLeft();									//"overloaded" moveTo funtion
	virtual void MoveRight();
	virtual void MoveForwards();
	virtual void MoveBackwards();
	virtual void MoveUp();
	virtual void MoveDown();

	virtual void SetHeight(byte*, int, int);

	virtual Vector3 GetPosition();
	virtual Vector3 GetRotation();

private:

	Vector3 rotation;
	Vector3 position;

	byte* heightData;
	int depth;
	int width;

	HWND* hwnd;
	InputHandler* inputHandler;

	float cameraHeight;
	bool lookingAt;

	float mouseX;
	float mouseY;

};
#endif // CAMERA_H_