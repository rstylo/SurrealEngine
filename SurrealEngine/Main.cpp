/*! \file  Main.cpp
\brief this class is used to move drawable objects around in the world
*/
#include <Windows.h>
#include <iostream>
#include "Kernel.h"

int main()
{
	Kernel kernel;
	std::cout << "Welcome at Surrealengine" << std::endl;
	std::string interfaceType;
	std::cout << "Would you like the 'beginner' or 'advanced' interface?:" << std::endl;
	while (interfaceType != "beginner" && interfaceType != "advanced") {
		std::cin >> interfaceType;
		if (interfaceType != "beginner" && interfaceType != "advanced")
			std::cout << "Please select one of the above" << std::endl;
	}
	//! The n00b interface
	if(interfaceType == "beginner"){
		//! intialises kernel and initiates its main routine
		if (kernel.Init(true))
				kernel.Update();
	}
	//! The sandbox interface
	if (interfaceType == "advanced") {
		int height, width, height2, width2;

		std::cout << "Please enter the window sizes" << std::endl;
		std::cout << "Window width: ";
		std::cin >> width;
		std::cout << "Window height: ";
		std::cin >> height;
		std::cout << "Window2 width: ";
		std::cin >> width2;
		std::cout << "Window2 height: ";
		std::cin >> height2;

		if (kernel.Init(true, width, height, width2, height2))
			kernel.Update();
	}
	exit(0);
	return 0;

}