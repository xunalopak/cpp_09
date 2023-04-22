//
// Created by Romain on 13/03/2023.
//

#ifndef CPP09_PMERGEME_HPP
#define CPP09_PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <string>
#include <sstream>
#include <stdexcept>

void merge_insertion_sort(std::vector<int>& arr, int l, int r);

void merge_insertion_sort_list(std::list<int>& lst, std::list<int>::iterator left, std::list<int>::iterator right, int threshold);

void fillVectorFromArgs(int ac, char **av, std::vector<int>& vec, std::list<int>& lst);

#endif //CPP09_PMERGEME_HPP
