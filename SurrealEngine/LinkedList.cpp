#include "LinkedList.h"
#include <iostream>
#include <string>

LinkedList::LinkedList(Node* n):head(n)
{
	
}

LinkedList::~LinkedList()
{
	Node* temp;
	delete head;
}

Node* LinkedList::getFirst()
{
	return head;
}

Node * LinkedList::getLast()
{
	if (head) {
		Node* temp = head;
		while (temp->getNext()) {
			temp = temp->getNext();
		}
		return temp;
	}
	return NULL;
}

void LinkedList::addLast(std::string naam)
{
	Node* nextnode = new Node(naam);
	getLast()->addNode(nextnode);
}

Node * LinkedList::find(std::string searchstring)
{
	Node* temp = head;
	while (temp->getNext() && temp->getString() != searchstring ) {
		temp = temp->getNext();
	}
	if (temp->getNext())
		return temp;
	log.log("Cannot find " + searchstring);
	return NULL;
}
