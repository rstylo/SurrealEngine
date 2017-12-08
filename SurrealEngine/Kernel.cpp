#include "Kernel.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "GameEntity.h"


Kernel::Kernel() : initialized(false) {}

Kernel::~Kernel() {}

bool Kernel::Init(HWND hWnd, bool windowed) {

	renderer = new Renderer();

	if (renderer->Init(hWnd, true)) 
	{
		resourceManager = new ResourceManager();

		sceneManager = new SceneManager();
		Scene* scene = sceneManager->GetCurrentScene();
		scene->Init(renderer->device);

		initialized = true;
		return true;
	}

	MessageBox(NULL, "failed initializing Game class", NULL, NULL);
	return false;
}

void Kernel::Update() 
{
	if (initialized)
	{
		renderer->Clear(D3DCOLOR_XRGB(0, 100, 100));
		renderer->Begin();

		Scene* scene = sceneManager->GetCurrentScene();
		scene->DrawEntities();

		renderer->End();
		renderer->Present();
	}
}