#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#define _USE_MATH_DEFINES
#include <d3dx9.h>
#include <string>
#include <cmath>



class Sprite;

class GameObject
{
public:
	GameObject(float, float, float, float, float);
	virtual ~GameObject();

	virtual bool Init();
	virtual bool IsInit();
	virtual void Update(float);
	virtual void AddSprite(Sprite*);
	virtual void SetSpeed(float);

	D3DXVECTOR3 velocity;
	float rotation;
	float speed;
	float maxSpeed;

private:

	bool initialized;
	Sprite* sprite;
};

#endif // GAMEOBJECT_H_