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

void merge_insertion_sort_list(std::list<int>& lst, std::list<int>::iterator left, std::list<int>::iterator right, int threshold) {
	if (std::distance(left, right) > 1) {
		if (std::distance(left, right) < threshold) {
			insertionSortList(left, right);
		} else {
			std::list<int>::iterator mid = std::next(left, std::distance(left, right) / 2);
			merge_insertion_sort_list(lst, left, mid, threshold);
			merge_insertion_sort_list(lst, mid, right, threshold);
			mergeList(left, mid, right);
		}
	}
}

void merge_insertion_sort(std::vector<int>& arr, int l, int r) {
	if (l >= r) {
		return;
	}

	// Si la taille du vecteur est inférieure à un seuil, on utilise l'algorithme d'insertion sort
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
