#include "Kernel.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
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

	if (inputHandler != NULL)
	{
		delete inputHandler;
		inputHandler = NULL;
	}
}

bool Kernel::Init(bool windowed) 
{

	
	Wnd* gameWnd = new Wnd(L"GameWindow", L"Game window", 1280, 720);						//window die de view van de game geeft
	Wnd* devWnd = new Wnd(L"DevWindow", L"Dev window", 640, 420);							//window die view van een andere persoctive geeft
	
	renderer = new DirectXRenderer();												

	if (gameWnd->Init(0, 0) && devWnd->Init(1280, 0))									//initialiseer beide windows
	{
		printf( "GameWindow and devWindow succefully initialised... \n" );
		if (renderer->Init(gameWnd->hWnd, true))
		{
			printf("GameRenderer and developersWindow succefully initialised... \n");

			gameDisplay = gameWnd;												//insert gamewnd en render in pair gameDisplay

			devDisplay = devWnd;													//insert devwnd en render in pair devDisplay

			inputHandler = new InputHandler(&gameWnd->hWnd);
			inputHandler->AddDevice(&devWnd->hWnd);
			sceneManager = new SceneManager(inputHandler);											//aanmaken van scenemanager
			resourceManager = new ResourceManager();
			
			device = renderer->GetDevice();

			sceneManager->SetupScene(*device);									

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
		renderer->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (renderer->Begin() && inputHandler->SetWnd(0))
		{
			sceneManager->Draw(*device, 0);
			renderer->End();
		}

		renderer->Present(gameDisplay->hWnd);


		//dev view
		renderer->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (renderer->Begin() && inputHandler->SetWnd(1))
		{
			sceneManager->Draw(*device, 1);
			renderer->End();
		}

		renderer->Present(devDisplay->hWnd);
	}
}



void Kernel::Update() {
	while (gameDisplay->Run() && devDisplay->Run()) 
	{	
		sceneManager->Update();
		resourceManager->Update();

		Draw();
	}
}
