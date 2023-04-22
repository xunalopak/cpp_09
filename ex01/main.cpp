//
// Created by Romain on 13/03/2023.
//

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Error: invalid number of arguments" << std::endl;
		std::cout << "Usage: ./RPN \"string\"" << std::endl;
		return 1;
	}

	std::stack<int> numbers;

	std::istringstream ss(av[1]);

	std::string token;
	while (ss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (numbers.size() < 2) {
				std::cout << "Error: Bad operation" << std::endl;
				return 1;
			}
			int n2 = numbers.top();
			numbers.pop();
			int n1 = numbers.top();
			numbers.pop();
			int result;
			if (token == "+")
				result = n1 + n2;
			else if (token == "-")
				result = n1 - n2;
			else if (token == "*")
				result = n1 * n2;
			else if (token == "/") {
				if (n2 == 0) {
					std::cout << "Error: Division by zero (apprend à faire des maths bouffon)" << std::endl;
					return 1;
				}
				result = n1 / n2;
			}
			numbers.push(result);
		}
		else {
			for(int i=0; token[i] !='\0'; i++) {
				if(token[i] < 48 || token[i] > 57) {
					std::cout << "Error: bad input" << std::endl;
					return 1;
				}
			}
			int num = atoi(token.c_str());
			numbers.push(num);
		}
	}

	if (numbers.size() != 1) {
		std::cout << "Error: Invalid input expression" << std::endl;
		return 1;
	}

	std::cout << numbers.top() << std::endl;
	return 0;
}
