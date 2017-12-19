#include <Windows.h>
#include <iostream>

#include "Kernel.h"

int main()											
{																								
	Kernel kernel;									

	if (kernel.Init(true))
			kernel.Update();

	exit(0);
	return 0;
}