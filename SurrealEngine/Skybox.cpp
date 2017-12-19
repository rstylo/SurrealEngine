#include "Skybox.h"



Skybox::Skybox()
{
	
}


Skybox::~Skybox()
{

}

bool Skybox::Init(LPDIRECT3DDEVICE9 device, std::string _texture)
{

	return false;
}

void Skybox::Update(D3DVECTOR position)
{
	middle.x = position.x;
	middle.y = position.y;
	middle.z = position.z;
}

void Skybox::Draw(LPDIRECT3DDEVICE9 device)
{

}
