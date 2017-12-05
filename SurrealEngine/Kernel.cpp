#include "Kernel.h"
#include "Renderer.h"
#include "Sprite.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "GameEntity.h"


Kernel::Kernel() : initialized(false)
{
	Manager* etyMngr = new EntityManager();
	Manager* rscMngr = new ResourceManager();

	managers.push_back(etyMngr);
	managers.push_back(rscMngr);
}


Kernel::~Kernel()
{
	for (auto mIt = managers.begin(); mIt != managers.end(); mIt++)
		if ((* mIt) == NULL)
		{
			delete (* mIt);
			(* mIt) = NULL;
		}
}

bool Kernel::Init(HWND hWnd, bool windowed) {

	renderer = new Renderer();
	myEntityManager = new EntityManager();

	if (renderer->Init(hWnd, true)) 
	{
		myEntityManager->Init(renderer->device);
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

		myEntityManager->DrawEntities();

		renderer->End();
		renderer->Present();
	}
}



void Kernel::Update() {
}

Manager* Kernel::GetManager(std::string managerType)
{
	/*
	for (std::list<Manager*>::const_iterator mIt = managers.begin(); mIt != managers.end(); mIt++)
	{
		if ((*mIt) != NULL && (*mIt)->GetManagerType() == managerType)
		{
			return (*mIt);
		}
	}
	*/
	return NULL;
}
