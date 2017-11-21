#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "Node.h"

class LinkedList {

public:
	LinkedList( Node* );
	virtual ~LinkedList();
	Node* getFirst();
	Node* getLast();
	void addLast( std::string );
	Node* find( std::string );

private:
	Node* head;
	Logger log;
};

#endif
