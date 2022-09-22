#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
using namespace std;

void heap_insert(vector<int>& arr, int val) {
	int parent_index=(arr.size()-1)/2;
	int val_index = arr.size();
	if (arr.size() == 0) {
		arr.push_back(val);
		return;
	}
	else {
		arr.push_back(val);
		while (1) {
			if (arr[parent_index] <= arr[val_index]) {
				return;
			}
			else {
				swap(arr[parent_index], arr[val_index]);
				val_index = parent_index;
				parent_index = (val_index - 1) / 2;
			}
		}
	}
}

int heap_extract(vector<int>& arr) {
	int result = arr[0];
	swap(arr[0], arr[arr.size() - 1]);
	arr.pop_back();
	int parent = 0;
	int first_child = parent * 2 + 1;
	int second_child = parent * 2 + 2;

	while (first_child < arr.size()) {
		if (second_child >= arr.size()) {
			if (arr[parent] > arr[first_child]) {
				swap(arr[first_child], arr[parent]);
			}
			return result;
		}
		if (arr[parent] <= arr[first_child] && arr[parent] <= arr[second_child]) {
			return result;
		}
		if (arr[first_child] <= arr[second_child]) {
			swap(arr[first_child], arr[parent]);
			parent = first_child;
			first_child = parent * 2 + 1;
			second_child = parent * 2 + 2;
		}
		else {
			swap(arr[second_child], arr[parent]);
			parent = second_child;
			first_child = parent * 2 + 1;
			second_child = parent * 2 + 2;
		}


	}
	return result;
}
void heapify_vector(vector<int>& arr) {
	vector<int> res;
	for (auto el : arr) {
		heap_insert(res, el);
	}
	arr = res;
}
void HeapSort(vector<int> & arr) {
	vector<int> result;
	while (arr.size() != 0) {
		result.push_back(heap_extract(arr));
	}
	arr = result;
}


//тест, де всі елементи однакові
bool test_1() {
	bool test_passed = true;
	vector<int> arr = { 1,1,1,1,1 };
	heapify_vector(arr);
	vector<int> test_arr = { 1,1,1,1,1 };
	HeapSort(arr);
	test_passed = test_passed && equal(arr.begin(), arr.end(), test_arr.begin());
	return test_passed;
}
//тест для сортування списку, який вже посортований спаданням
bool test_reverse() {
	bool test_passed = true;
	vector<int> arr = { 9,8,6,4,1 };
	heapify_vector(arr);
	vector<int> test_arr = { 1,4,6,8,9 };
	HeapSort(arr);
	test_passed = test_passed && equal(arr.begin(), arr.end(), test_arr.begin());
	return test_passed;
}
//рандомний тест, який створює 100 списків з елементами до 99 та звіряє результат нашої 
//функції з методом .sort() 
bool test_random() {
	bool test_passed = true;
	for (int i = 0; i < 100; i++) {
		vector<int> arr;
		srand(time(0)+rand());
		for (int j = 0; j < 100; j++) {
			heap_insert(arr, rand() % 100);
		}
		vector<int> arr2 = arr;
		vector<int> failed = arr;
		sort(arr2.begin(), arr2.end());
		HeapSort(arr);
		test_passed = test_passed && equal(arr.begin(), arr.end(), arr2.begin());
	}
	return test_passed;
}
int main() {
	cout << "test_1: " << (test_1() ? "passed" : "failed") << endl;
	cout << "test_reverse: " << (test_reverse() ? "passed" : "failed") << endl;
	cout << "test_random: " << (test_random() ? "passed" : "failed") << endl;
}