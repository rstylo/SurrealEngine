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
	expert = false;
	//! initialises renderer, window, scenemanager and console and creates a starting scene

	gameDisplay = new Wnd("GameWindow", "Game window", 1280, 720);						//window die de view van de game geeft
	devDisplay = new Wnd("DevWindow", "Dev window", 640, 420);							//window die view van een andere persoctive geeft
	SetWindowPos(GetConsoleWindow(),0,1280,420,0,0, SWP_NOSIZE|SWP_NOZORDER);


	renderer = new DirectXRenderer();
	//renderer = new OpenGLRenderer();

	if (gameDisplay->Init(0, 0) && devDisplay->Init(1280, 0))									//initialiseer beide windows
	{
		printf("GameWindow and devWindow succefully initialised... \n");
		renderer->Log("GameWindow and devWindow succefully initialised...", "Info");
		if (renderer->Init(gameDisplay->hWnd, true))
		{
			printf("GameRenderer succefully initialised... \n");
			renderer->Log("GameRenderer succefully initialised...", "Info");
			inputHandler = new InputHandler();
			if (inputHandler->Init(&gameDisplay->hWnd)) {
				inputHandler->SetWindow(&gameDisplay->hWnd);
				printf("Input handler succefully initialized... \n");
				renderer->Log("Input handler succefully initialized...", "Info");

				sceneManager = new SceneManager();											//aanmaken van scenemanager
				sceneManager->Init(renderer);
				sceneManager->LoadSceneFromFile("level.txt");


				console = new Console(sceneManager,expert);

				initialized = true;
				return true;
			}
		}
	}
	


	MessageBox(NULL, "failed initializing Game class", NULL, NULL);
	return false;
}

bool Kernel::Init(bool windowed,int width, int height, int width2, int height2)
{
	expert = true;

	gameDisplay = new Wnd("GameWindow", "Game window", width, height);						//window die de view van de game geeft
	devDisplay = new Wnd("DevWindow", "Dev window", width2, height2);							//window die view van een andere persoctive geeft

	std::string rendertype, levelchoice, level;
	std::cout << "Renderer (choose between 'directx' and 'opengl'):  ";
	while (rendertype != "directx" && rendertype != "opengl") {
		std::cin >> rendertype;
		if(rendertype != "directx" && rendertype != "opengl")
			std::cout << "Please select one of the above" << std::endl;
		if (rendertype == "opengl") {
			std::cout << "OpenGL is not available yet, DirectX is automatically chosen" << std::endl;
			rendertype = "directx";
		}
	}
	std::cout << "Would you like to create a scene or import a levelfile? (please enter 'import' or 'create'):" << std::endl;
	while (levelchoice != "import" && levelchoice != "create") {
		std::cin >> levelchoice;
		if (levelchoice != "import" && levelchoice != "create")
			std::cout << "Please select one of the above" << std::endl;
	}
	if (levelchoice == "import") {
		std::cout << "Enter the levelfile you want to import: ";
		std::cin >> level;
	}

	if(rendertype == "directx")
		renderer = new DirectXRenderer();
	if (rendertype == "opengl")
		renderer = new OpenGLRenderer();

	SetWindowPos(GetConsoleWindow(), 0, width, height2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	if (gameDisplay->Init(0, 0) && devDisplay->Init(width, 0))									//initialiseer beide windows
	{
		printf("GameWindow and devWindow succefully initialised... \n");
		renderer->Log("GameWindow and devWindow succefully initialised...", "Info");
		if (renderer->Init(gameDisplay->hWnd, true))
		{
			printf("GameRenderer succefully initialised... \n");
			renderer->Log("GameRenderer succefully initialised...", "Info");
			inputHandler = new InputHandler();
			if (inputHandler->Init(&gameDisplay->hWnd)) {
				inputHandler->SetWindow(&gameDisplay->hWnd);
				printf("Input handler succefully initialized... \n");
				renderer->Log("Input handler succefully initialized...", "Info");

				sceneManager = new SceneManager();											

				if (levelchoice == "import")
					sceneManager->LoadSceneFromFile(level);
				else
					sceneManager->CreateLevel();

				console = new Console(sceneManager, expert);

				initialized = true;
				return true;
			}
		}
	}
	logger.Log("failed initializing Game class", "Error");
	return false;
}

void Kernel::Draw()
{
	//! Initiates drawing routine
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
	bool hpressed = false;
	bool bpressed = false;
	int logtime = 0;
	//! Initiates Updating routine
	while (gameDisplay->Run() && devDisplay->Run() && !inputHandler->CheckKeyboardPressed('`')) //~ gebruikt als char voor escape
	{
		if (*inputHandler->GetWindow() != GetFocus()) {
			if (devDisplay->hWnd == GetFocus())
				inputHandler->SetWindow(&devDisplay->hWnd);
			else if (gameDisplay->hWnd == GetFocus())
				inputHandler->SetWindow(&gameDisplay->hWnd);
		}

		if (sceneManager->IsLoading() == true) {
			sceneManager->SetupScene(renderer, inputHandler, &gameDisplay->hWnd, &devDisplay->hWnd);
			std::cout << "Press 'h' to view the help/command list" << std::endl << std::endl;
		}
		sceneManager->Update();
		
		if (inputHandler->CheckKeyboardPressed('b')) {
			if (bpressed == false) {
				std::cout << "Enter a command: " << std::endl;
				SetFocus(GetConsoleWindow());
				bpressed = true;
			}
		}
		else {
			if (bpressed == true)
				bpressed = false;
		}
		
		if (inputHandler->CheckKeyboardPressed('h')) {
			if (hpressed == false) {
				console->PrintHelp();
				std::cout << std::endl;
				hpressed = true;
			}
		}
		else {
			if(hpressed == true)
				hpressed = false;
		}
		
		if (inputHandler->CheckKeyboardPressed('b')) {
			console->ReadLine();
		}
		console->Update();
		inputHandler->Update();
		
		Draw();

		logtime++;
		if (logtime > 10) {
			renderer->Flush();
			logtime = 0;
		}
	}
}