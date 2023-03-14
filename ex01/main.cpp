//
// Created by Romain on 13/03/2023.
//

#include <iostream>
#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2)
	{
		std::cout << "Error: invalid number of arguments" << std::endl;
		std::cout << "Usage: ./RPN \"string\"" << std::endl;
		return 1;
	}
	rpn(av);
	return 0;
}
