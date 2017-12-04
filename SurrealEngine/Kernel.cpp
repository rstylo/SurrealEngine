#include "Kernel.h"
#include "Renderer.h"
#include "Sprite.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Entity.h"


Kernel::Kernel()
	: initialized(false)
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

bool Kernel::Init(HWND hWnd, HWND hWnd2, bool windowed) {

	renderer = new Renderer();
	renderer2 = new Renderer();

	if (renderer->Init(hWnd, windowed) && renderer2->Init(hWnd2, windowed))
	{
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

		for (auto mIt = managers.begin(); mIt != managers.end(); mIt++)
			{
				(*mIt)->Draw();
			}

		renderer->End();
		renderer->Present();
	}
	
	if (initialized)
	{
		renderer2->Clear(D3DCOLOR_XRGB(100, 50, 100));
		renderer2->Begin();

		for (auto mIt = managers.begin(); mIt != managers.end(); mIt++)
		{
			(*mIt)->Draw();
		}

		renderer2->End();
		renderer2->Present();
	}
}

bool Kernel::CreateEntity(std::string name, int h, int w, float x, float y, float z)
{
	if (initialized) 
	{	
		Entity* entity = new Entity(x , y, z);
		Sprite* sprite = new Sprite();

		if (sprite->Init(renderer->device, name, h, w)) {												//check of de naam naar de directory wel echt bestaat
			entity->AddSprite(sprite);

			if (dynamic_cast<EntityManager*>(GetManager("EntityManager")))								//check of er in lijst van managers een Entity manager in zit
			{
				dynamic_cast<EntityManager*>(GetManager("EntityManager"))->AddEntity(entity);			//zodat voeg  de entity toe
			}

			if (dynamic_cast<ResourceManager*>(GetManager("ResourceManager")))
			{
				dynamic_cast<ResourceManager*>(GetManager("ResourceManager"))->AddResource(sprite);
			}

			return true;
		}
		return false;
	}

	return false;
}

void Kernel::Update() {
	for (auto mIt = managers.begin(); mIt != managers.end(); mIt++)
	{
		if ((*mIt) != NULL)
		{
			(*mIt)->Update();
		}
	}
}

Manager* Kernel::GetManager(std::string managerType)
{
	for (std::list<Manager*>::const_iterator mIt = managers.begin(); mIt != managers.end(); mIt++)
	{
		if ((*mIt) != NULL && (*mIt)->GetManagerType() == managerType)
		{
			return (*mIt);
		}
	}
	return NULL;
}
