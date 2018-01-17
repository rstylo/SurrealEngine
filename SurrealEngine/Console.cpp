#include "Console.h"
#include "SceneManager.h"



Console::Console(SceneManager* _sceneManager)
{
	
	sceneManager = _sceneManager;

	//commands
	commands["spawn entity"] = &SceneManager::SpawnEntity;				//set value to static ponter to member of scenemanager 
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
	if (commands.find(commandText) != commands.end())
		(sceneManager->*(commands.find(commandText)->second))();		//call function from current sceneManager
	else
		PrintL("command not found....");
}

void Console::PrintHelp()
{
	PrintL("List of commands:");
	for (auto it = commands.begin(); it != commands.end(); it++)
	{
		PrintL(it->first);
	}
	PrintL("'-' or enter to quit read line");
}

void Console::ReadLine()
{
	 std::cout << std::endl;

	std::getline(std::cin, currentLine);


	
}
void Console::Update()
{
	if (currentLine != "-" && currentLine != "")													//- is char for stopping inbut
	{
		int wordCount = -1;																			//if wordcount is still -1 means that the currentLine was empty
		bool inWord = false;																		//needed to switch between words

		std::string param[10];																		//every word, decided by spaces, is inserted into this array
		
		for (int currentChar = 0; currentChar < currentLine.size(); currentChar++)					//for each letter in the current lne
		{
			if (currentLine[currentChar] != ' ')													//if its not space then its a word	else its the start of a new word	
			{
				if (inWord == false)																//start new word if last char was a space
				{
					wordCount++;
					inWord = true;
				}

				if (wordCount < 10)
					param[wordCount] += currentLine[currentChar];									//add current letter at the end of the currentword				
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
