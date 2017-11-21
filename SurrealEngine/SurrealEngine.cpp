#include <iostream>
#include "logger.h"
#include <string>
#include "LinkedList.h"

int main()
{
	Logger l1;
	l1.logtime();

	LinkedList* list1 = new LinkedList(new Node("nummer 1"));
	list1->addLast("nummer 2");
	list1->addLast("nummer 3");
	list1->find("nummer 2");
	list1->find("asd");
	delete list1;
	
	
	while (1) {
		std::string text1;
		std::cin >> text1;
		l1.log(text1);
	}
    return 0;
}

