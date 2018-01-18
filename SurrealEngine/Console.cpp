#include "Console.h"
#include "SceneManager.h"



Console::Console(SceneManager* _sceneManager)
{
	
	sceneManager = _sceneManager;
	//! registers àll command functions in scenemanager by using a void pointer to static member of scenemanager
	//! 
	commands["spawn mesh"] = &SceneManager::SpawnEntityMesh;						
	commands["spawn object"] = &SceneManager::SpawnEntityObject;						
	commands["set scene"] = &SceneManager::SetScene;
	commands["create scene"] = &SceneManager::CreateScene;
	commands["change terrain"] = &SceneManager::ChangeTerrain;
	commands["move entity"] = &SceneManager::MoveEntity;
	commands["move terrain"] = &SceneManager::MoveTerrain;
	commands["save scene"] = &SceneManager::SaveScene;

	currentLine = "-";
}


Console::~Console()
{
}
void Console::DoCommand(std::string commandText)
{
	//! check and do the command if possible, by calling the void* to memeber of scenemanager it with a scenemanager object
	if (commands.find(commandText) != commands.end())
		(sceneManager->*(commands.find(commandText)->second))();		
	else
		PrintL("command not found....");
}

void Console::PrintHelp()
{
	//! prints a list of all registerd commands
	PrintL("List of commands:");
	for (auto it = commands.begin(); it != commands.end(); it++)
	{
		PrintL(it->first);
	}
	PrintL("'-' or enter to quit read line");
}

void Console::ReadLine()
{
	//! get current line in console
	 std::cout << std::endl;

	std::getline(std::cin, currentLine);


	
}
void Console::Update()
{
	//! splits the read line into parameters, and calls doCommand with the first 2 words of the line
	if (currentLine != "-" && currentLine != "")													//! '-' is the char for stopping console input
	{
		int wordCount = -1;																			// if wordcount is still -1 means that the currentLine was empty
		bool inWord = false;																		// needed to switch between words

		std::string param[10];																		//! every word, decided by spaces, is inserted into a array
		
		for (int currentChar = 0; currentChar < currentLine.size(); currentChar++)					//! for each letter in the current lne
		{
			if (currentLine[currentChar] != ' ')													//! if its not a space then its a word,	else its the start of a new word	
			{
				if (inWord == false)																//! starst new word if last char was a space
				{
					wordCount++;
					inWord = true;
				}

				if (wordCount < 10)
					param[wordCount] += currentLine[currentChar];									//! adds current letter at the end of the currentword				
			}
			else
			{
				inWord = false;																		
			}
		}

		if (param[0] == "help")
		{
			PrintHelp();
		}

		DoCommand(param[0] + " " + param[1]);

		currentLine = "-";
	}

	


}

std::string Console::GetLine()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
}
void Console::Print(std::string text)
{
	std::cout << text;
}

void Console::PrintL(std::string text)
{
	std::cout << text << std::endl;
}
