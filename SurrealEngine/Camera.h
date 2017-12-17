#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>

class InputHandler;

class Camera
{
public:
	Camera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3, InputHandler*);
	virtual ~Camera();

	virtual void SetupView(LPDIRECT3DDEVICE9);
	virtual void LookAt(D3DXVECTOR3);
	virtual void Update(int cam);
	virtual void MoveTo(D3DXVECTOR3);
	void Rotate(float, float);
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveForwards();
	virtual void MoveBackwards();
	virtual void MoveUp();

	virtual void MoveDown();

private:
	
	D3DXVECTOR3 position;

	D3DXVECTOR3 rotation;
	D3DXVECTOR3 translation;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 up;

	InputHandler* inputHandler;


};
#endif // CAMERA_H_
