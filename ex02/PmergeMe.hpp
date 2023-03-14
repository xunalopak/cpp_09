//
// Created by Romain on 13/03/2023.
//

#ifndef CPP09_PMERGEME_HPP
#define CPP09_PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>

class PmergeMe{
private:
	std::vector<int> vector_;
	std::list<int> list_;

public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const &src);
	PmergeMe &operator=(PmergeMe const &rhs);

	void printVector();
	void printList();
	static bool isNumber(const char *tab);
	void ft_sort();
	void ft_exec(char **tab);
	double VectorSort();
	double ListSort();

};


#endif //CPP09_PMERGEME_HPP
