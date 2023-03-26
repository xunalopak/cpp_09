//
// Created by Romain on 13/03/2023.
//

#include "PmergeMe.hpp"

void printVector(std::vector<int> &vec){
	int i = 0;
	if (vec.size() > 8){
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++){
			i++;
			if (i == 8){
				std::cout << "... ";
				break;
			}
			std::cout << *it << " ";
		}
	}
	else{
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << " ";
	}

	std::cout << std::endl;
}

void printList(std::list<int> &lst){
	if (lst.size() > 8){
		int i = 0;
		for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++){
			i++;
			if (i == 8){
				std::cout << "... ";
				break;
			}
			std::cout << *it << " ";
		}
	}
	else{
		for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
			std::cout << *it << " ";
	}
	std::cout << std::endl;
}

int main(int ac, char **av){
	if (ac < 3)
		throw std::invalid_argument("Error: Invalid number of arguments.");
	std::vector<int> vec;
	std::list<int> lst;

	try{
		fillVectorFromArgs(ac, av, vec);
		int n = vec.size();
		std::cout << "Before: ";
		printVector(vec);
		clock_t start = clock();
		double elapsed_secs_lst = mergeInsertionSort(vec, lst, n);
		clock_t end = clock();
		double elapsed_secs_vec = double(end - start) / CLOCKS_PER_SEC * 1000;
		std::cout << "After: ";
		printList(lst);
		std::cout << "Time to process a range of " << n << " elements with std::vector : " << elapsed_secs_vec << " us" << std::endl;
		std::cout << "Time to process a range of " << n << " elements with std::list : " << elapsed_secs_lst << " us" << std::endl;

	}
	catch (std::exception &e){
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
