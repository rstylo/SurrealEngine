#include "Kernel.h"
#include "Renderer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "GameEntity.h"


Kernel::Kernel() : initialized(false) {}

Kernel::~Kernel() {}

bool Kernel::Init(HWND hWnd, bool windowed) {

	renderer = new Renderer();
	myScene = new Scene();

	if (renderer->Init(hWnd, true)) 
	{
		myScene->Init(renderer->device);
		initialized = true;
		return true;
	}

	MessageBox(NULL, "failed initializing Game class", NULL, NULL);
	return false;
}

void Kernel::Draw()
{
	if (initialized) 
	{
		renderer->Clear(D3DCOLOR_XRGB(0, 100, 100));
		renderer->Begin();

		myScene->DrawEntities();

		renderer->End();
		renderer->Present();
	}
}

void Kernel::Update() {}