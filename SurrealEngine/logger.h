#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <fstream>

class Logger {

public:
	Logger();
	virtual ~Logger();
	void logtime();
	void log( int );
	void log( std::string );
	void flush();

private:
	std::ofstream file1;
};

#endif