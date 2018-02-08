#include "Kernel.h"
#include "Renderer.h"
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
	//! call scenemanager destructor
	if (sceneManager != NULL)		
	{
		delete sceneManager;
		sceneManager = NULL;
	}

	//! call to inputhandler destructor
	if (inputHandler != NULL)
	{
		delete inputHandler;
		inputHandler = NULL;
	}

	//! call to console destructor
	if (console != NULL)
	{
		delete console;
		console = NULL;
	}

	//! call to window destructor
	if (gameDisplay != NULL)
	{
		delete gameDisplay;
		gameDisplay == NULL;
	}

	//! call to window destrutor
	if (devDisplay != NULL)
	{
		delete devDisplay;
		devDisplay = NULL;
	}
}

bool Kernel::Init(bool windowed)
{

	expert = false;

	//! initialises renderer, window, scenemanager and console and creates a starting scene

	gameDisplay = new Wnd("GameWindow", "Game window", 1280, 720);						//window with game perpective
	devDisplay = new Wnd("DevWindow", "Dev window", 640, 420);							//window with a different perpective
	SetWindowPos(GetConsoleWindow(),0,1280,420,0,0, SWP_NOSIZE|SWP_NOZORDER);			//sets console window position


	renderer = new DirectXRenderer();													//initialise with directxRenderer
	//renderer = new OpenGLRenderer();

	if (gameDisplay->Init(0, 0) && devDisplay->Init(1280, 0))									//initalise both windows
	{
		printf("GameWindow and devWindow succefully initialised... \n");
		renderer->Log("GameWindow and devWindow succefully initialised...", "Info");
		if (renderer->Init(gameDisplay->hWnd, true))											//initialise the renderer with a hWnd in windowed mode
		{
			printf("GameRenderer succefully initialised... \n");
			renderer->Log("GameRenderer succefully initialised...", "Info");

			inputHandler = new InputHandler();													//create a dx input handler
			if (inputHandler->Init(&gameDisplay->hWnd)) {										//initialise with starting window
				inputHandler->SetWindow(&gameDisplay->hWnd);									//set window
				printf("Input handler succefully initialized... \n");
				renderer->Log("Input handler succefully initialized...", "Info");

				sceneManager = new SceneManager();											//creates scenemanager for managing scenes
				sceneManager->Init(renderer);												//initialises with a generic renderer
				sceneManager->LoadSceneFromFile("level.txt");								//loads a scene from level text file


				console = new Console(sceneManager,expert);									//create a console class for managing commands

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
	//! initialises renderer, window, scenemanager and console and creates a starting scene
	expert = true;

	gameDisplay = new Wnd("GameWindow", "Game window", width, height);						
	devDisplay = new Wnd("DevWindow", "Dev window", width2, height2);							

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
		//draw game view
		renderer->Clear(0x0000FFFF);					//clear the backbuffer with color in rgb 0,255,255
		if (renderer->Begin())							//start capturing new backbuffer
		{
			sceneManager->Draw(renderer, 0);			//draws current scene into the backbuffer from perspective view 0
			renderer->End();							//end
		}

		renderer->Present(gameDisplay->hWnd);			//Present the current backbuffer the game window, !!!will present nothing if begin was unsucceful


		//draw dev view
		renderer->Clear(D3DCOLOR_XRGB(0, 255, 255));
		if (renderer->Begin())
		{
			sceneManager->Draw(renderer, 1);		//draws current scene into the backbuffer from perspective view 0
			renderer->End();
		}

		renderer->Present(devDisplay->hWnd);	//Present the current backbuffer to the dev window, !!!will present nothing if begin was unsucceful
	}
}

void Kernel::Update() {
	bool hpressed = false;
	bool bpressed = false;
	int logtime = 0;
	//! Initiates Updating routine
	while (gameDisplay->Run() && devDisplay->Run() && !inputHandler->CheckKeyboardPressed('`')) //~ gebruikt als char voor escape
	{
		//! set the window the user is currently focused on as the window to get input from
		if (*inputHandler->GetWindow() != GetFocus()) {
			if (devDisplay->hWnd == GetFocus())
				inputHandler->SetWindow(&devDisplay->hWnd);
			else if (gameDisplay->hWnd == GetFocus())
				inputHandler->SetWindow(&gameDisplay->hWnd);
		}

		//! call with a renderer to Setup the scene if needed
		if (sceneManager->IsLoading() == true) {
			sceneManager->SetupScene(renderer, inputHandler, &gameDisplay->hWnd, &devDisplay->hWnd);
			std::cout << "Press 'h' to view the help/command list" << std::endl << std::endl;
		}

		//! call to scenemanager updating routine
		sceneManager->Update();
		
		//! check if command key("b") is pressed, to set console window as the focused window
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
		
		//! check if help key("h") is pressed
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
		
		//! read input if command key is pressed
		if (inputHandler->CheckKeyboardPressed('b')) {
			console->ReadLine();
		}


		//! updates the console
		console->Update();

		//! updates the inputhandler
		inputHandler->Update();
		
		//! calls kernel drawing routine
		Draw();

		logtime++;
		if (logtime > 10) {
			renderer->Flush();
			logtime = 0;
		}
	}
}