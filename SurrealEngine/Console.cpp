#include "Console.h"
#include "SceneManager.h"



Console::Console(SceneManager* _sceneManager)
{
	
	sceneManager = _sceneManager;
	//void *funct = (void**)(sceneManager->SpawnEntity);	//werkt nog niet
	//RegisterCommands("SpawnEntity", funct);

}


Console::~Console()
{
}

bool Console::RegisterCommands(std::string commandText, void* fct)
{
	if(commands.find(commandText) != commands.end())
		return false;

	commands[commandText] = fct;
}

bool Console::CheckCommand(std::string)
{
	return false;
}

void Console::DoCommand(std::string commandText)
{
//	if (commands.find(commandText) != commands.end())
		//((func_type)commands.find(commandText)->second)();
	sceneManager->SpawnEntity();
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
		std::cout << currentLine << std::endl;
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

		if (param[0] == "create" && param[1] == "entity")
		{
			DoCommand("SpawnEntity");
		}
		else
		{
			std::cout << "command not found" << std::endl;
		}

		currentLine = " ";
	}

	


}

void Console::Print(std::string text)
{
	std::cout << text;
}

void Console::PrintL(std::string text)
{
	std::cout << text << std::endl;
}
