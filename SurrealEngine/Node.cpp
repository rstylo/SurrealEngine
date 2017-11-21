#include "Node.h"


Node::Node(std::string naam): naam(naam)
{
}

Node::~Node()
{
	log.log("deleting " + getString());
	delete next;
	log.log("deleted " + getString());
	next = NULL;
}



void Node::addNode(Node* list1)
{
	log.log("node " + list1->getString() + " has been added");
	next = list1;
}

Node* Node::getNext()
{
	return next;
}

void Node::addString(std::string s1)
{
	naam = s1;
}

std::string Node::getString()
{
	return naam;
}
