#include "Kernel.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"
#include "Wnd.h"

#include "SceneManager.h"
#include "Console.h"
#include "InputHandler.h"




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

	if (inputHandler != NULL)
	{
		delete inputHandler;
		inputHandler = NULL;
	}
}

bool Kernel::Init(bool windowed)
{
	

	gameDisplay = new Wnd("GameWindow", "Game window", 1280, 720);						//window die de view van de game geeft
	devDisplay = new Wnd("DevWindow", "Dev window", 640, 420);							//window die view van een andere persoctive geeft


	renderer = new DirectXRenderer();
	//renderer = new OpenGLRenderer();

	if (gameDisplay->Init(0, 0) && devDisplay->Init(1280, 0))									//initialiseer beide windows
	{
		printf("GameWindow and devWindow succefully initialised... \n");
		if (renderer->Init(gameDisplay->hWnd, true))
		{
			printf("GameRenderer and developersWindow succefully initialised... \n");

			inputHandler = new InputHandler();
			if (inputHandler->Init(&gameDisplay->hWnd)) {
				inputHandler->SetWindow(&gameDisplay->hWnd);
				printf("Input handler succefully initialized... \n");

				sceneManager = new SceneManager();											//aanmaken van scenemanager
				//sceneManager->CreateScene("Scene0");
				//sceneManager->LoadScene("Scene0");
				sceneManager->LoadSceneFromFile("level.txt");


				console = new Console(sceneManager);

				initialized = true;
				return true;
			}
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
		renderer->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (renderer->Begin())
		{
			sceneManager->Draw(renderer, 0);
			renderer->End();
		}

		renderer->Present(gameDisplay->hWnd);


		//dev view
		renderer->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (renderer->Begin())
		{
			sceneManager->Draw(renderer, 1);
			renderer->End();
		}

		renderer->Present(devDisplay->hWnd);
	}
}

void Kernel::Update() {
	while (gameDisplay->Run() && devDisplay->Run() && !inputHandler->CheckKeyboardPressed('`')) //~ gebruikt als char voor escape
	{
		if (*inputHandler->GetWindow() != GetFocus()) {
			if (devDisplay->hWnd == GetFocus())
				inputHandler->SetWindow(&devDisplay->hWnd);
			else if (gameDisplay->hWnd == GetFocus())
				inputHandler->SetWindow(&gameDisplay->hWnd);
		}

		if (sceneManager->IsLoading() == true)
			sceneManager->SetupScene(renderer, inputHandler, &gameDisplay->hWnd, &devDisplay->hWnd);

		sceneManager->Update();


		console->Update();
		if(inputHandler->CheckKeyboardPressed('b'))
			console->ReadLine();

		inputHandler->Update();
		Draw();
	}
}