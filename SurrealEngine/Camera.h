/*
* Name: Camera.h
* Description: This class is used for setting up the view matrix of the current scene
* Note: no actual scene is needed for use of this class
*/


#ifndef CAMERA_H_
#define CAMERA_H_

#include "Renderer.h"
#include <d3dx9.h>
#include "InputHandler.h"

class Camera
{
public:
	Camera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, HWND*, InputHandler*);				//HWND with the window in which the view is to be displayed and a inputhandler from witch it can get real time input
	virtual ~Camera();

	virtual void SetupView(Renderer*);																//rendering routine

	virtual void LookAt(D3DXVECTOR3);																//change the lookAt vector
	virtual void SetLookAt(bool);

	virtual void Update();																			//main routine, used for moving and rotating the view matrix

	virtual void MoveTo(float);																		//move the camera towards a certain angle
	virtual void Rotate(float, float);																//rotate transform pitch and yaw

	virtual void MoveLeft();																		//"overloaded" moveTo funtion
	virtual void MoveRight();
	virtual void MoveForwards();
	virtual void MoveBackwards();
	virtual void MoveUp();
	virtual void MoveDown();

	virtual D3DXVECTOR3 GetPosition();
	virtual D3DXVECTOR3 GetRotation();

private:

	D3DXVECTOR3 rotation;
	D3DXVECTOR3 position;

	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 up;

	HWND* hwnd;
	InputHandler* inputHandler;

	float cameraHeight;
	bool lookingAt;



};
#endif // CAMERA_H_