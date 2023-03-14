//
// Created by Romain on 13/03/2023.
//

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
	if (this != &rhs) {
		this->list_ = rhs.list_;
		this->vector_ = rhs.vector_;
	}
	return *this;
}

void PmergeMe::printVector(){
	int i = 0;
	for (std::vector<int>::iterator it = vector_.begin(); it < vector_.end(); it++)
	{
		if(++i > 5)
		{
			std::cout << " [...]";
			break;
		}
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void PmergeMe::printList(){
	int i = 0;
	for (std::list<int>::iterator it = list_.begin(); it != list_.end(); it++)
	{
		if(++i > 5)
		{
			std::cout << " [...]";
			break;
		}
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

bool PmergeMe::isNumber(const char *tab) {
	std::string str = tab;
	if (str[0] == '-'){
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (str.length() > 10 || (str.length() == 10 && str > "2147483647")){
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	if (!str.empty() && str.find_first_not_of("0123456789") != std::string::npos){
		std::cout << "Error: not a number." << std::endl;
		return false;
	}
	return true;
}

double PmergeMe::VectorSort() {
	std::clock_t start, end;
	int	n, temp;
	double result;

	start = clock();
	n = vector_.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (vector_[j] > vector_[j + 1])
			{
				temp = vector_[j];
				vector_[j] = vector_[j + 1];
				vector_[j + 1] = temp;
			}
		}
	}
	end = clock();
	result = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
	return result;
}

double PmergeMe::ListSort() {
	std::clock_t start, end;
	double result;
	int temp;

	start = clock();
	for (std::list<int>::iterator i = ++list_.begin(); i != list_.end(); ++i)
	{
		temp = *i;
		std::list<int>::iterator j = i;
		while (j != list_.begin() && *(--j) > temp)
		{
			*(++j) = *j;
			j--;
		}
		*(++j) = temp;
		j--;
	}
	end = clock();
	result = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
	return result;
}

void PmergeMe::ft_exec(char **tab) {
	double VectorTime, ListTime;
	int i = 1;
	int nb = 0;

	while (tab[i]) {
		if (!isNumber(tab[i]))
			return;
		std::istringstream(tab[i]) >> nb;
		vector_.push_back(nb);
		list_.push_back(nb);
		i++;
	}
	std::cout << "Before: ";
	printVector();
	ListTime = ListSort();
	VectorTime = VectorSort();
	std::cout << "After: ";
	printVector();
	std::cout << "Time to process a range of " << vector_.size() <<" elements with std::vector : " << VectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << vector_.size() <<" elements with std::list : " << ListTime << " us" << std::endl;
}

