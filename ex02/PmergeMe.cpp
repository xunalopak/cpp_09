//
// Created by Romain on 13/03/2023.
//

#include "PmergeMe.hpp"

void insertionSortList(std::list<int>& l) {
	for (std::list<int>::iterator it = ++l.begin(); it != l.end(); ++it) {
		int key = *it;
		std::list<int>::iterator j = it;
		--j;
		while (j != l.begin() && *j > key) {
			*it = *j;
			--j;
			--it;
		}
		*it = key;
	}
}

void mergeSortList(std::list<int>& l) {
	if (l.size() < 10) {
		return;
	}
	std::list<int> left, right;
	int mid = l.size() / 2;
	for (std::list<int>::iterator i = l.begin(); i != l.end(); i++) {
		if (distance(l.begin(), i) < mid) {
			left.push_back(*i);
		} else {
			right.push_back(*i);
		}
	}
	l.clear();
	mergeSortList(left);
	mergeSortList(right);
	while (!left.empty() && !right.empty()) {
		if (left.front() <= right.front()) {
			l.push_back(left.front());
			left.pop_front();
		} else {
			l.push_back(right.front());
			right.pop_front();
		}
	}
	while (!left.empty()) {
		l.push_back(left.front());
		left.pop_front();
	}
	while (!right.empty()) {
		l.push_back(right.front());
		right.pop_front();
	}
}

void merge_insertion_sort_list(std::list<int>& lst) {
	if (lst.size() < 2)
		insertionSortList(lst);
	else {
		mergeSortList(lst);
	}
}

void merge_insertion_sort(std::vector<int>& arr, int l, int r) {
	if (l >= r) {
		return;
	}

	// Si la taille du vecteur est inférieure à un seuil, on utilise l'algorithme d'insertion
	if (r - l + 1 <= 10) {
		for (int i = l + 1; i <= r; i++) {
			int key = arr[i];
			int j = i - 1;
			while (j >= l && arr[j] > key) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	} else {
		int m = (l + r) / 2;
		merge_insertion_sort(arr, l, m);
		merge_insertion_sort(arr, m + 1, r);

		// Fusionner les deux sous-vecteurs triés
		std::vector<int> merged;
		int i = l, j = m + 1;
		while (i <= m && j <= r) {
			if (arr[i] <= arr[j]) {
				merged.push_back(arr[i]);
				i++;
			} else {
				merged.push_back(arr[j]);
				j++;
			}
		}
		while (i <= m) {
			merged.push_back(arr[i]);
			i++;
		}
		while (j <= r) {
			merged.push_back(arr[j]);
			j++;
		}

		// Copier les éléments fusionnés dans le vecteur d'origine
		for (int i = l; i <= r; i++) {
			arr[i] = merged[i - l];
		}
	}
}

void fillVectorFromArgs(int ac, char **av, std::vector<int>& vec, std::list<int>& lst) {
	for (int i = 1; i < ac; i++) {
		std::istringstream ss(av[i]);
		int num;
		if (ss >> num) {
			vec.push_back(num);
			lst.push_back(num);
		} else {
			throw std::invalid_argument("Invalid argument: " + std::string(av[i]));
		}
	}
}
