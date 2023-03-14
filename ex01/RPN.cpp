//
// Created by Romain on 13/03/2023.
//

#include <iostream>
#include <stack>

int isUsable(char c){
	if (c >= '0' && c <= '9')
		return 1;
	else if (c == '+' || c == '-' || c == '/' || c == '*')
		return 2;
	return 0;
}

void operation(std::stack<int> &rpn_stack, char c){
	int n1, n2;
	if (c == '+')
	{
		n1 = rpn_stack.top();
		rpn_stack.pop();
		n2 = rpn_stack.top();
		rpn_stack.pop();
		rpn_stack.push(n2 + n1);
	}
	else if (c == '-')
	{
		n1 = rpn_stack.top();
		rpn_stack.pop();
		n2 = rpn_stack.top();
		rpn_stack.pop();
		rpn_stack.push(n2 - n1);
	}
	else if (c == '*')
	{
		n1 = rpn_stack.top();
		rpn_stack.pop();
		n2 = rpn_stack.top();
		rpn_stack.pop();
		rpn_stack.push(n2 * n1);
	}
	else if (c == '/')
	{
		if (rpn_stack.top() == 0)
		{
			std::cout << "Error: Cannot devide by zero" << std::endl;
			return;
		}
		n1 = rpn_stack.top();
		rpn_stack.pop();
		n2 = rpn_stack.top();
		rpn_stack.pop();
		rpn_stack.push(n2 / n1);
	}
}

void rpn(char **av){
	std::stack<int> rpn_stack;

	for (int i = 0; av[1][i]; i++){
		if (av[1][i] == ' ')
			continue;
		else if (isUsable(av[1][i]) == 1)
			rpn_stack.push(av[1][i] - '0');
		else if (isUsable(av[1][i]) == 2){
			if (rpn_stack.size() < 2){
				std::cout << "Error: Not enough arguments" << std::endl;
				return;
			}
			operation(rpn_stack, av[1][i]);
		}
		else if (isUsable(av[1][i]) == 0){
			std::cout << "Error: Invalid character" << std::endl;
			return;
		}
	}
	std::cout << rpn_stack.top() << std::endl;
}