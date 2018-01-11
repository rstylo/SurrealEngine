#include "Console.h"
#include "SceneManager.h"



Console::Console(SceneManager* _sceneManager)
{
	
	sceneManager = _sceneManager;

	//commands
	commands["spawn entity"] = &SceneManager::SpawnEntity;
	commands["set scene"] = &SceneManager::SetScene;
	commands["create scene"] = &SceneManager::CreateScene;
	commands["change terrain"] = &SceneManager::ChangeTerrain;


}


Console::~Console()
{
}

bool Console::CheckCommand(std::string)
{
	return false;
}

void Console::DoCommand(std::string commandText)
{
	if (commands.find(commandText) != commands.end())
		(sceneManager->*(commands.find(commandText)->second))();

}

void Console::PrintHelp()
{
	PrintL("List of commands:");
	for (auto it = commands.begin(); it != commands.end(); it++)
	{
		PrintL(it->first);
	}
}

void Console::ReadLine()
{
	 std::cout << std::endl;

	std::getline(std::cin, currentLine);


	
}
void Console::Update()
{
	if (currentLine != " ")
	{
		int wordCount = -1;
		bool inWord = false;

		std::string param[10];
		
		for (int currentChar = 0; currentChar < currentLine.size(); currentChar++)
		{
			if (currentLine[currentChar] != ' ')
			{
				if (inWord == false)
				{
					wordCount++;
					inWord = true;
				}

				if (wordCount < 10)
					param[wordCount] += currentLine[currentChar];
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

		if (param[0] + " " + param[1] == "spawn entity" )
		{
			DoCommand("spawn entity");
		}
		else if (param[0] + " " + param[1] == "set scene")
		{
			DoCommand("set scene");
		}
		else if (param[0] + " " + param[1] == "create scene")
		{
			DoCommand("create scene");
		}
		else if (param[0] + " " + param[1] == "change terrain")
		{
			DoCommand("change terrain");
		}
		else
		{
			std::cout << "command not found" << std::endl;
		}

		currentLine = " ";
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
