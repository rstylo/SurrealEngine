#include "GameObject.h"
#include "Sprite.h"



GameObject::GameObject(float x, float y, float _rotation, float _speed, float _maxSpeed) : rotation(_rotation), speed(_speed), maxSpeed(_maxSpeed)
{
	//maximale rotatie 2 x 
	float pi2 = (float)(M_PI * 2);
	position.x = x;
	position.y = y;
	position.z = 0;

	if (_rotation > pi2) _rotation = pi2;
	if (_rotation < 0) _rotation = 0;

	if (_speed > _maxSpeed) _speed = _maxSpeed;
	if (_speed > 0) _speed = 0;

	rotation = _rotation;
	speed = _speed;

	velocity.x = cos(rotation) * _speed;
	velocity.y = sin(rotation) * _speed;
	velocity.z = 0;

	maxSpeed = _maxSpeed;

	
}



GameObject::~GameObject()
{
	if (sprite != NULL)
		delete sprite;	sprite = NULL;
}

bool GameObject::Init() {
	initialized = true;
	return true;
}

bool GameObject::IsInit() {


	return initialized;
}

void GameObject::Update(float time) {
	position.x += velocity.x;
	position.y += velocity.y;

	if (sprite != NULL)
	{
		sprite->Draw(time, position);
	}
}

void GameObject::AddSprite(Sprite* _sprite)
{
	if (sprite != NULL) {
		delete sprite;
		sprite = NULL;
	}

	sprite = _sprite;
}

void GameObject::SetSpeed(float _speed)
{
	if(_speed >= 0 && _speed <= maxSpeed)
	{
		speed = _speed;

		velocity.x = cos(rotation) * _speed;
		velocity.y = sin(rotation) * _speed;
		velocity.z = 0;
	}
}