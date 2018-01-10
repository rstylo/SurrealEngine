#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
#include <iostream>
#include <d3d9.h>

typedef void(*func_type)(void);

class SceneManager;
class Scene;

class Console
{
public:
	Console(SceneManager*);
	virtual ~Console();

	virtual bool RegisterCommands(std::string, void*);
	virtual bool CheckCommand(std::string);

	virtual void ReadLine();
	virtual void DoCommand(std::string param);

	virtual void Update();
	virtual void Print(std::string);
	virtual void PrintL(std::string);

private:
	std::string currentLine;

	SceneManager* sceneManager;
	std::map<std::string, void*> commands;
};

#endif CONSOLE_H_