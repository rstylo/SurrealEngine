#include "Manager.h"



Manager::Manager(std::string _managerType)
	: managerType(_managerType)				//toekenen van type naam die gebruikt wordt voor het herkennen van welke childklasse deze base klasse heeft
{
}


Manager::~Manager()
{

}

std::string Manager::GetManagerType()
{
	return managerType;
}
