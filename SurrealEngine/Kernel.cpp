#include "Kernel.h"
#include "Renderer.h"
#include "Wnd.h"

#include "SceneManager.h"
#include "ResourceManager.h"






Kernel::Kernel()
	: initialized(false)
{
}


Kernel::~Kernel()
{
	if (sceneManager != NULL)
	{
		delete sceneManager;
		sceneManager = NULL;
	}

	if (resourceManager != NULL)
	{
		delete resourceManager;
		resourceManager = NULL;
	}

	if (gameDisplay.first != NULL) 
	{
		delete gameDisplay.first;
		gameDisplay.first = NULL;
	}
		

	if (gameDisplay.second != NULL)
	{
		delete gameDisplay.second;
		gameDisplay.second = NULL;
	}

	if (devDisplay.first != NULL)
	{
		delete devDisplay.first;
		devDisplay.first = NULL;
	}


	if (devDisplay.second != NULL)
	{
		delete devDisplay.second;
		devDisplay.second = NULL;
	}

}

bool Kernel::Init(bool windowed) 
{
	
	
	Wnd* gameWnd = new Wnd("GameWindow", "Game window", 1280, 720);						//window die de view van de game geeft
	Wnd* devWnd = new Wnd("DevWindow", "Dev window", 640, 420);							//window die view van een andere persoctive geeft
	
	Renderer* gameRend = new Renderer();												
	Renderer* devRend = new Renderer();													

	if (gameWnd->Init(0, 0) && devWnd->Init(1280, 0))									//initialiseer beide windows
	{
		printf( "GameWindow and devWindow succefully initialised... \n" );
		if (gameRend->Init(gameWnd->hWnd, true) && devRend->Init(devWnd->hWnd, true))
		{
			printf("GameRenderer and developersWindow succefully initialised... \n");

			gameDisplay.first = gameWnd;												//insert gamewnd en render in pair gameDisplay
			gameDisplay.second = gameRend;

			devDisplay.first = devWnd;													//insert devwnd en render in pair devDisplay
			devDisplay.second = devRend;

			sceneManager = new SceneManager();											//aanmaken van scenemanager
			resourceManager = new ResourceManager(&gameRend->device);

			sceneManager->SetupScene(gameRend->device);									

			initialized = true;
			return true;
		}
	}

	

	MessageBox(NULL, "failed initializing Game class", NULL, NULL);
	return false;
}

void Kernel::Draw()
{
	if (initialized) 
	{
		//gameView
		gameDisplay.second->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (gameDisplay.second->Begin())
		{
			//sceneManager->Draw(gameDisplay.second->device, 0);
			resourceManager->Draw();

			gameDisplay.second->End();
		}

		gameDisplay.second->Present();


		//dev view
		devDisplay.second->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (devDisplay.second->Begin())
		{
			sceneManager->Draw(devDisplay.second->device, 1);
			devDisplay.second->End();
		}

		devDisplay.second->Present();
	}
}



void Kernel::Update() {
	if(gameDisplay.first->Run() && devDisplay.first->Run()) 
	{	
		sceneManager->Update();
		resourceManager->Update();

		Draw();
	}
}
