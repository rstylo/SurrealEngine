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

void Logger::Logtime() {

	//! print current time into the log
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
	totaltime << timestruct.tm_mday << "/" << timestruct.tm_mon+1 << "/" << timestruct.tm_year+1900 << " - " << timestruct.tm_hour << ":" << minuten;
	Log(totaltime.str());
}

void Logger::Log(std::string text)
{
	//! log text
	file1.open("logfile.txt", std::ios::app);
	file1 << text;
	file1 << std::endl;
	file1.close();
}

void Logger::Log(int value)
{
	//! log a number
	file1.open("logfile.txt", std::ios::app);
	file1 << value;
	file1 << std::endl;
	file1.close();
}

void Logger::Log(std::string text, std::string type)
{
	//! log error type
	Logtime();
	file1.open("logfile.txt", std::ios::app);
	file1 << "<<" << type << ">>" << std::endl;
	file1 << text;
	file1 << std::endl;
	file1.close();
}

void Logger::Flush() {
	file1.flush();
}