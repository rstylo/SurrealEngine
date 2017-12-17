#include <Windows.h>
#include <iostream>

#include "Kernel.h"

int main()											
{																								
	Kernel kernel;									

	if (kernel.Init(true))
		while(1)
		{
			kernel.Update();
		}

	return 0;
}