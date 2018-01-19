/*! \file  Logger.h
\brief Logs a message
*/


#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>

class Logger {

public:
	Logger();
	virtual ~Logger();

	virtual void Logtime();
	virtual void Log( int );
	virtual void Log( std::string );
	virtual void Log( std::string, std::string );
	void Flush();

private:
	std::ofstream file1;
};

#endif