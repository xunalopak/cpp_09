//
// Created by Romain on 13/03/2023.
//

#ifndef CPP09_PMERGEME_HPP
#define CPP09_PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <string>
#include <sstream>
#include <stdexcept>

void insertionSort(std::vector<int>::iterator left, std::vector<int>::iterator right);
void merge(std::vector<int>::iterator left_it, std::vector<int>::iterator mid_it, std::vector<int>::iterator right_it);
void mergeSort(std::vector<int>& arr, std::vector<int>::iterator left_it, std::vector<int>::iterator right_it, int k);
void mergeInsertionSort(std::vector<int>& arr, std::list<int>& lst, int n);

void fillVectorFromArgs(int ac, char **av, std::vector<int>& vec);

#endif //CPP09_PMERGEME_HPP
