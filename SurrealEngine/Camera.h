#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>
#include "InputHandler.h"

class Camera
{
public:
	Camera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, HWND*, InputHandler*);
	virtual ~Camera();

	virtual void SetupView(LPDIRECT3DDEVICE9);
	virtual void LookAt(D3DXVECTOR3);
	virtual void Update();
	virtual void MoveTo(D3DXVECTOR3);
	virtual void Rotate(float, float);

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveForwards();
	virtual void MoveBackwards();
	virtual void MoveUp();
	virtual void MoveDown();

	virtual D3DXVECTOR3 GetPosition();

private:

	D3DXVECTOR3 rotation;
	D3DXVECTOR3 position;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 up;

	HWND* hwnd;
	InputHandler* inputHandler;


};
#endif // CAMERA_H_