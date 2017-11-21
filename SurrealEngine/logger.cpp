#include <iostream>
#include <string>
#include <fstream>
#include "logger.h"
#include <time.h>
#include <sstream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::logtime() {
	time_t  now;
	struct tm timestruct;
	now = time(NULL);
	localtime_s(&timestruct, &now);
	std::string minuten = "0";
	if (timestruct.tm_min < 10)
		minuten.append(std::to_string(timestruct.tm_min));
	else 
		minuten = std::to_string(timestruct.tm_min);
	std::stringstream totaltime;
	totaltime << timestruct.tm_mday << "/" << timestruct.tm_mon << "/" << timestruct.tm_year+1900 << " - " << timestruct.tm_hour << ":" << minuten;
	log(totaltime.str());
}


void Logger::log(std::string text1)
{
	file1.open("logfile.txt", std::ios::app);
	file1 << text1;
	file1 << std::endl;
	std::cout << text1 << std::endl;
	file1.close();
}