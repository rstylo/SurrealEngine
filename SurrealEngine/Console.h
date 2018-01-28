/*! \file Concole.h
	\brief This class is used for reading and calling commands. It can als be use to print text on to the console
*/

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
#include <iostream>
#include <d3d9.h>
#include "Logger.h"



class SceneManager;
class Scene;

class Console
{
public:
	Console(SceneManager*, bool);						//! must have a seen manager to work
	virtual ~Console();

	virtual void ReadLine();					//! read current line in console
	virtual void Update();						//! checks if currentline is a command
	virtual void DoCommand(std::string param);	//! function to trigger a command

	

	virtual void Print(std::string);			
	virtual void PrintL(std::string);
	virtual void PrintHelp();					//! print list of commands

	virtual std::string GetLine();

private:
	std::string currentLine;

	SceneManager* sceneManager;
	std::map<std::string, void(SceneManager::*)(void)> commands;	//! map with command name as the key and void* to a scenemanager function scenemanager as value
	Logger logger;
};

//
#endif // CONSOLE_H_