#include <iostream>
#include <string>
#include <fstream>
#include "Logger.h"
#include <time.h>
#include <sstream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Logtime() {
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
	totaltime << timestruct.tm_mday << "/" << timestruct.tm_mon << "/" << timestruct.tm_year+1900 << 
		" - " << timestruct.tm_hour << ":" << minuten << " - " << timestruct.tm_sec << "s";
	Log(totaltime.str());
}

void Logger::Log(int value)
{
	file.open("logfile.txt", std::ios::app);
	file << value;
	file << std::endl;
	file.close();
}

void Logger::Log(std::string text)
{
	file.open("logfile.txt", std::ios::app);
	file << text;
	file << std::endl;
	file.close();
}

void Logger::Log(std::string text, std::string type)
{
	Logtime();
	file.open("logfile.txt", std::ios::app);
	file << "<<" << type << ">>";
	file << text;
	file << std::endl;
	file.close();
}

void Logger::Flush() {
	file.flush();
}