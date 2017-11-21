#ifndef _NODE_H_
#define	_NODE_H_

#include "logger.h"
#include <string>

class Node {

public:
	Node(std::string);
	virtual ~Node();
	void addNode(Node*);
	Node* getNext();
	void addString(std::string);
	std::string getString();


private:
	Node* next;
	std::string naam;
	Logger log;
};


#endif