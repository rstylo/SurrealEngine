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
	void Log( std::string );
	void Flush();

private:
	std::ofstream file1;
};

#endif