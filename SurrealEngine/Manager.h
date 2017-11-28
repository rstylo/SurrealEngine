#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "logger.h"

class Manager {

public:
	virtual ~Manager();
	virtual int Update() = 0;
	virtual int Render() = 0;

private:
	int updatePriority();
	int renderPriority();
	Logger* logger;
};

#endif