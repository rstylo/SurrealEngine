#include <Windows.h>
#include <iostream>

#include "Kernel.h"
#include "Wnd.h"

//windows api main functie
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)												//hPrevInstance always null, lpCmdLine = commandline van de instance
{																									//window to be handel

	Wnd wnd(hInstance, nCmdShow, "MainWindow", "First window :D", 1280, 720);

	if (wnd.Init())																				//maak nieuwe window aam
	{
		Kernel kernel;

		if (kernel.Init((wnd.hWnd), true)) 
		{
			if (kernel.CreateEntity("BobMarley.png", 340, 340, 150, 150, 0))					//test functie 
			{							
				while (true)
				{
					if (wnd.Run())
					{

						kernel.Update();

						kernel.Draw();
					}
					else
					{
						break;
					}	

					
				}
			}
		}

	}
	return 0;
}