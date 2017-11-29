#ifndef MANAGER_H_
#define MANAGER_H_

#include <string>

class Manager
{
public:
	Manager(std::string);
	virtual ~Manager();

	virtual void Update() = 0;
	virtual void Draw() = 0;			

	std::string GetManagerType();

protected:
	//hier(priority) nog geen gebruikt van gemaakt
	int priority;
	int updatePriority;
	int renderPriority;

	std::string managerType;


};

#endif // MANAGER_H_