//
// Created by Romain on 13/03/2023.
//

#include "PmergeMe.hpp"


void insertionSortDeque(std::deque<int>& arr) {
	int n = arr.size();

	for (int i = 1; i < n; ++i) {
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}


void mergeDeque(std::deque<int>& arr, int left, int mid, int right) {
	std::deque<int> leftArr(mid - left + 1);
	std::deque<int> rightArr(right - mid);

	for (size_t i = 0; i < leftArr.size(); ++i) {
		leftArr[i] = arr[left + i];
	}

	for (size_t i = 0; i < rightArr.size(); ++i) {
		rightArr[i] = arr[mid + 1 + i];
	}

	size_t i = 0, j = 0, k = left;

	while (i < leftArr.size() && j < rightArr.size()) {
		if (leftArr[i] <= rightArr[j]) {
			arr[k] = leftArr[i];
			i++;
		} else {
			arr[k] = rightArr[j];
			j++;
		}

		k++;
	}

	while (i < leftArr.size()) {
		arr[k] = leftArr[i];
		i++;
		k++;
	}

	while (j < rightArr.size()) {
		arr[k] = rightArr[j];
		j++;
		k++;
	}
}

void mergeSortDeque(std::deque<int>& arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSortDeque(arr, left, mid);
		mergeSortDeque(arr, mid + 1, right);
		mergeDeque(arr, left, mid, right);
	}
}

void merge_insertion_sort_deque(std::deque<int>& arr, int left, int right) {
	if (right - left < 15) {
		insertionSortDeque(arr);
	} else {
		int mid = (left + right) / 2;
		merge_insertion_sort_deque(arr, left, mid);
		merge_insertion_sort_deque(arr, mid + 1, right);
		mergeDeque(arr, left, mid, right);
	}
}


void merge(std::vector<int>& vec, int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> L(n1);
	std::vector<int> R(n2);

	for (i = 0; i < n1; i++)
		L[i] = vec[left + i];
	for (j = 0; j < n2; j++)
		R[j] = vec[mid + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			vec[k] = L[i];
			i++;
		} else {
			vec[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		vec[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		vec[k] = R[j];
		j++;
		k++;
	}
}

void merge_insertion_sort(std::vector<int>& l, int left, int right) {
	if (left < right) {
		if (right - left <= 15) {
			// tri insertion
			for (int i = left + 1; i <= right; i++) {
				int key = l[i];
				int j = i - 1;

				while (j >= left && l[j] > key) {
					l[j + 1] = l[j];
					j--;
				}

				l[j + 1] = key;
			}
		} else {
			int mid = left + (right - left) / 2;
			merge_insertion_sort(l, left, mid);
			merge_insertion_sort(l, mid + 1, right);
			merge(l, left, mid, right);
		}
	}
}

void fillVectorFromArgs(int ac, char **av, std::vector<int>& vec, std::deque<int>& deq) {
	for (int i = 1; i < ac; i++) {
		std::istringstream ss(av[i]);
		int num;
		if (ss >> num) {
			vec.push_back(num);
			deq.push_back(num);
		} else {
			throw std::invalid_argument("Invalid argument: " + std::string(av[i]));
		}
	}
}
