//
// Created by Romain on 13/03/2023.
//

#include "PmergeMe.hpp"

void insertionSortList(std::list<int>::iterator left, std::list<int>::iterator right) {
	for (std::list<int>::iterator i = left; i != right; ++i) {
		int key = *i;
		std::list<int>::iterator j = i;
		while (j != left && *std::prev(j) > key) {
			*j = *std::prev(j);
			--j;
		}
		*j = key;
	}
}

void mergeList(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right) {
	std::list<int> leftLst(left, mid);
	std::list<int> rightLst(mid, right);

	std::list<int>::iterator i = leftLst.begin();
	std::list<int>::iterator j = rightLst.begin();
	std::list<int>::iterator k = left;

	while (i != leftLst.end() && j != rightLst.end()) {
		if (*i <= *j) {
			*k = *i;
			++i;
		} else {
			*k = *j;
			++j;
		}
		++k;
	}

	while (i != leftLst.end()) {
		*k = *i;
		++i;
		++k;
	}

	while (j != rightLst.end()) {
		*k = *j;
		++j;
		++k;
	}
}

void mergeInsertionSortList(std::list<int>& lst, std::list<int>::iterator left, std::list<int>::iterator right, int threshold) {
	if (std::distance(left, right) > 1) {
		if (std::distance(left, right) < threshold) {
			insertionSortList(left, right);
		} else {
			std::list<int>::iterator mid = std::next(left, std::distance(left, right) / 2);
			mergeInsertionSortList(lst, left, mid, threshold);
			mergeInsertionSortList(lst, mid, right, threshold);
			mergeList(left, mid, right);
		}
	}
}

void insertionSort(std::vector<int>::iterator left, std::vector<int>::iterator right) {
	for (std::vector<int>::iterator i = left + 1; i != right; i++) {
		int key = *i;
		std::vector<int>::iterator j = i - 1;
		while (j >= left && *j > key) {
			*(j + 1) = *j;
			j--;
		}
		*(j + 1) = key;
	}
}

void merge(std::vector<int>::iterator left_it, std::vector<int>::iterator mid_it, std::vector<int>::iterator right_it) {
	int n1 = mid_it - left_it + 1;
	int n2 = right_it - mid_it;

	std::vector<int> L(n1);
	std::vector<int> R(n2);

	for (int i = 0; i < n1; i++) {
		L[i] = *(left_it + i);
	}
	for (int j = 0; j < n2; j++) {
		R[j] = *(mid_it + 1 + j);
	}

	int i = 0;
	int j = 0;
	std::vector<int>::iterator k = left_it;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			*k = L[i];
			i++;
		}
		else {
			*k = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		*k = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		*k = R[j];
		j++;
		k++;
	}
}

void mergeSort(std::vector<int>& arr, std::vector<int>::iterator left_it, std::vector<int>::iterator right_it, int k) {
	if (left_it < right_it) {
		if (right_it - left_it <= k) {
			insertionSort(left_it, right_it);
		}
		else {
			std::vector<int>::iterator mid_it = left_it + (right_it - left_it) / 2;
			mergeSort(arr, left_it, mid_it, k);
			mergeSort(arr, mid_it + 1, right_it, k);
			merge(left_it, mid_it, right_it);
		}
	}
}

double mergeInsertionSort(std::vector<int>& arr, std::list<int>& lst, int n) {
	if (arr.empty()) {
		throw std::invalid_argument("Error: The array cannot be empty.");
	}
	int k = 7; // seuil pour le tri par insertion
	for (int i = 0; i < n; i++) {
		lst.push_back(arr[i]);
	}
	mergeSort(arr, arr.begin(), arr.end(), k);
	clock_t start = clock();
	mergeInsertionSortList(lst, lst.begin(), lst.end(), k);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC * 1000;
}

void fillVectorFromArgs(int ac, char **av, std::vector<int>& vec) {
	for (int i = 1; i < ac; i++) {
		std::istringstream ss(av[i]);
		int num;
		if (ss >> num) {
			vec.push_back(num);
		} else {
			throw std::invalid_argument("Invalid argument: " + std::string(av[i]));
		}
	}
}
