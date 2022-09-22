#include<iostream>
#include<list>
#include <algorithm>
#include<chrono>
using namespace std;
//функція для злиття двох списків
void MergeLists(list<int>& result, const list<int>& li) {
	auto li_it = li.begin();
	auto result_it = result.begin();
	while (li_it != li.end()) {
		if (result_it==result.end()|| *li_it <= *result_it ) {
			result.insert(result_it, *li_it);
			li_it++;
			result_it = result.begin();
		}
		else {
			result_it++;
		}
	}
}
void StrandSort(list<int>& arr) {
	list<int> strand, result;
	while (!arr.empty()) {
		auto arr_it = arr.begin();
		auto strand_it = strand.insert(strand.begin(), *arr_it);
		arr_it= arr.erase(arr_it);
		while (arr_it != arr.end()) {
			if (*strand_it <= *arr_it) {
				++strand_it;
				strand_it = strand.insert(strand_it, *arr_it);
				arr_it= arr.erase(arr_it);
			}
			else {
				++arr_it;
			}
		}
		MergeLists(result, strand);
		strand.clear();
	}
	arr = result;
}
//тест, де всі елементи однакові
bool test_1() {
	bool test_passed = true;
	list<int> li = { 1,1,1,1,1 };
	list<int> test_li = { 1,1,1,1,1};
	StrandSort(li);
	test_passed = test_passed && equal(li.begin(), li.end(), test_li.begin());
	return test_passed;
}
//тест для сортування списку, який вже посортований спаданням
bool test_reverse() {
	bool test_passed = true;
	list<int> li = {9,8,6,4,1};
	list<int> test_li = {1,4,6,8,9};
	StrandSort(li);
	test_passed = test_passed && equal(li.begin(), li.end(), test_li.begin());
	return test_passed;
}
//рандомний тест, який створює 100 списків з елементами до 99 та звіряє результат нашої 
//функції з методом .sort() 
bool test_random() {
	bool test_passed = true;
	for (int i = 0; i < 100; i++) {
		list<int> li;
		srand(time(0)+i);
		for (int j = 0; j < 100; j++) {
			li.push_back(rand() % 100);
		}
		list<int> li2=li;
		li2.sort();
		StrandSort(li);
		test_passed = test_passed && equal(li.begin(), li.end(), li2.begin());
	}
	return test_passed;
}

int main() {
	cout << "test_1: " << (test_1() ? "passed" : "failed") << endl;
	cout << "test_reverse: " << (test_reverse() ? "passed" : "failed") << endl;
	cout << "test_random: " << (test_random() ? "passed" : "failed") << endl;
}