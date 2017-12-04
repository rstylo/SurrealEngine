
#include <windows.h>
#include <iostream>
#include <string>

#include "Kernel.h"
#include "Wnd.h"

/*
* 1. Om de code te kunnen runnen, moet onder project properties -> vc++ -> included directories deze path toevoegen
* 	C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include.
* 2. vc++ -> liblary directiories
* 	C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86
* 3. daarna onder properties -> linker -> input -> Addiotional dependencies d3d9.lib en d3dx9.lib bij schrijven
* 4. verder  is het belangrijk dat het project op multi-bit rund anders werken LPSTR niet voor sommige van de windows functies
voeg hier * voor uncomment>
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	 //hPrevInstance always null, lpCmdLine commandline van de instance
{																									//window to be handel

	Wnd wnd(hInstance, nCmdShow, "MainWindow", "First window :D", 1280, 720, 100, 100);
	Wnd wnd2(hInstance, nCmdShow, "SecondWindow", "Second window ^_^", 860, 640, 1000, 300);

	if (wnd.Init() && wnd2.Init())																				//maak nieuwe window aam
	{
		Kernel kernel;

		if (kernel.Init((wnd.hWnd), (wnd2.hWnd), true))
		{
			if (kernel.CreateEntity("BobMarley.png", 340, 340, 150, 150, 0))					//test functie 
			{							
				while (true)
				{
					wnd.Run();

					kernel.Update();

					kernel.Draw();
					
				}
			}
		}

	}
	return 0;
}

