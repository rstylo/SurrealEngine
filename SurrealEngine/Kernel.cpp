#include "Kernel.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "ResourceManager.h"

//tempolary, deze klassen horen geen relatie te hebben met kernel
#include "Entity.h"
#include "Object.h"
#include "Scene.h"
#include "Sprite.h"

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

	if (object != NULL)
	{
		delete object;
		object = NULL;
	}
	
	if (scene != NULL)
	{
		delete scene;
		scene = NULL;
	}
}

bool Kernel::Init(HWND hWnd, bool windowed) {

	renderer = new Renderer();


	if (renderer->Init(hWnd, true)) 
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
		renderer->Clear(D3DCOLOR_XRGB(70, 250, 0));
		if (renderer->Begin())
		{
			scene->SetupMatrices(renderer->device);
			object->Draw(renderer->device);

			for (auto mIt = managers.begin(); mIt != managers.end(); mIt++)
			{
				(*mIt)->Draw();
			}

			renderer->End();
			
		}

		renderer->Present();
	}
}

bool Kernel::CreateEntity(std::string name, int h, int w, float x, float y, float z)
{
	if (initialized) 
	{	
		//Entity* entity = new Entity(x , y, z);
		//Sprite* sprite = new Sprite();

		D3DXVECTOR3 eye(0.0f, 10.0f, -20.0f);
		D3DXVECTOR3 lookAt(0.0f, 0.0f, 0.0f);
		scene = new Scene(eye, lookAt);
		object = new Object();
		

		//if (sprite->Init(renderer->device, name, h, w)) {												//check of de naam naar de directory wel echt bestaat
			//entity->AddSprite(sprite);

			//if (dynamic_cast<EntityManager*>(GetManager("EntityManager")))								//check of er in lijst van managers een Entity manager in zit
			//{
				//dynamic_cast<EntityManager*>(GetManager("EntityManager"))->AddEntity(entity);			//voeg  de entity toe
			//}

			//if (dynamic_cast<ResourceManager*>(GetManager("ResourceManager")))
			//{
				//dynamic_cast<ResourceManager*>(GetManager("ResourceManager"))->AddResource(sprite);
			//}

		if (object->Init(renderer->device))
			return true;
		//}
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
