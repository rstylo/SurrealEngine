#include "Kernel.h"
#include "Renderer.h"
#include "Wnd.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputHandler.h"

#include "Scene.h"
#include "Camera.h"


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
}

bool Kernel::Init(bool windowed) 
{

	
	Wnd* gameWnd = new Wnd(L"GameWindow", L"Game window", 1280, 720);						//window die de view van de game geeft
	Wnd* devWnd = new Wnd(L"DevWindow", L"Dev window", 640, 420);							//window die view van een andere persoctive geeft
	
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
			resourceManager = new ResourceManager();
			
			sceneManager->SetupScene(gameRend->device);									

			inputHandler = new InputHandler(&gameWnd->hWnd);
			inputHandler->Acquire();

			initialized = true;
			return true;
		}
	}

	

	MessageBox(NULL, L"failed initializing Game class", NULL, NULL);
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
			sceneManager->Draw(gameDisplay.second->device, 0);
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
	while (gameDisplay.first->Run() && devDisplay.first->Run()) 
	{	
		sceneManager->Update();
		resourceManager->Update();
		inputHandler->Update(sceneManager->GetCurrentScene()->GetCamera(0));

		Draw();
	}
}
