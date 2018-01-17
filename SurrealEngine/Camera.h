/*! \file Camera.h
	\brief This class is used for setting up the view matrix of the current scene
*/



#ifndef CAMERA_H_
#define CAMERA_H_

#include "Renderer.h"
#include <d3dx9.h>
#include "InputHandler.h"
#include "Transform.h"

const float pi = 3.141592654f;																		

class Camera
{
public:
	Camera(Vector3, Vector3, HWND*, InputHandler*);													//!  HWND with the window in which the view is to be displayed and a inputhandler from witch it can get real time input
	virtual ~Camera();

	virtual void SetupView(Renderer*);																//! rendering routine 

	virtual void SetLookAt(bool);																	//! set lookat position for the camera to look at

	virtual void Update();																			//!  main routine, used for moving and rotating the camera

	virtual void MoveTo(float);																		//!  move the camera towards a certain angle
	virtual void Rotate(float, float);																//!  rotate transform pitch and yaw 

	virtual void MoveLeft();																		//! "overloaded" moveTo funtion
	virtual void MoveRight();
	virtual void MoveForwards();
	virtual void MoveBackwards();
	virtual void MoveUp();
	virtual void MoveDown();

	virtual Vector3 GetPosition();
	virtual Vector3 GetRotation();

private:

	Vector3 rotation;																				//!  variable holding rotation vector
	Vector3 position;																				//!  variable holding position vector

	D3DXVECTOR3 up;																					//!  variable defining what up is from the views perspective

	HWND* hwnd;																						//!  pointer pointing to the window for which the cam is displaying, generally used for checking if a window is focussed on
	InputHandler* inputHandler;																		//!  pointer to inputhandler class, from which camera can get inputs

	float cameraHeight;																				
	bool lookingAt;

	float mouseX;
	float mouseY;



};
#endif // CAMERA_H_