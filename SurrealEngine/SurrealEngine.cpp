#include <iostream>
#include "logger.h"
#include <string>

int main()
{
	Logger l1;
	l1.logtime();

	while (1) {
		std::string text1;
		std::cin >> text1;
		l1.log(text1);
	}
    return 0;
}

