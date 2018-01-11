#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
#include <iostream>
#include <d3d9.h>



class SceneManager;
class Scene;

class Console
{
public:
	Console(SceneManager*);
	virtual ~Console();

	virtual bool CheckCommand(std::string);

	virtual void ReadLine();
	virtual void DoCommand(std::string param);

	virtual void Update();
	virtual void Print(std::string);
	virtual void PrintL(std::string);
	virtual void PrintHelp();

	virtual std::string GetLine();

private:
	std::string currentLine;

	SceneManager* sceneManager;
	std::map<std::string, void(SceneManager::*)(void)> commands;
};

//
#endif // CONSOLE_H_