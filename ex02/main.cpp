//
// Created by Romain on 13/03/2023.
//

#include "PmergeMe.hpp"

int main(int ac, char **av) {

	PmergeMe pmergeMe;
	if (ac == 1){
		std::cout << "Error: no arguments." << std::endl;
		return 0;
	}
	pmergeMe.ft_exec(av);
	return 0;
}