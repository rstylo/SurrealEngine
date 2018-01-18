/*! \file  Main.cpp
\brief this class is used to move drawable objects around in the world
*/
#include <Windows.h>
#include <iostream>

#include "Kernel.h"

int main()											
{																								
	Kernel kernel;									

	//! intialises kernel and initiates its main routine
	if (kernel.Init(true))
			kernel.Update();

	exit(0);
	return 0;
}