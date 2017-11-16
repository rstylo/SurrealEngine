#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

class Logger {

public:
	Logger();
	virtual ~Logger();
	void logtime();
	void log(std::string);

private:
	std::ofstream file1;
};

#endif