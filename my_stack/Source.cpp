#include <iostream>
#include<stack>
using namespace std;

class IntStack
{
private:
	int* container_;
	//розмір для того щоб не здійснювати лишніх копіювань
	unsigned int size_=1;
	//індекс першої вільної комірки , а також розмір, тобто кількість елементів в стеку
	unsigned int index_of_empty_element_ = 0;
public:
	IntStack():container_(new int[size_]){
		//container_ = new int[size_];
	}
	~IntStack(){
		delete[]container_;
	}
	unsigned int getSize() {
		return index_of_empty_element_;
	}
	void push(int new_element)
	{
		if (index_of_empty_element_ + 1 == size_) {
			//creating new bigger container
			size_ *= 2;
			int* new_container = new int[size_];
			for (int i = 0; i < index_of_empty_element_ + 1; i++) {
				new_container[i] = container_[i];
			}
			delete[]container_;
			container_ = new_container;
		}
		//adding new item
		container_[index_of_empty_element_] = new_element;
		index_of_empty_element_++;
	}
	int pop()
	{
		if (this->is_empty()) { 
			cout << "impossible to pop, stack is empty!" << endl;
			return NULL; }
		//todo:check if not empty!!!
		int ret_val = container_[index_of_empty_element_ - 1];
		index_of_empty_element_--;

		//in case if we are going to pop elements a lot of times, it will help to save memory
		if (size_ - index_of_empty_element_ > 100) {
			//creating new smaller container
			size_ -= 50;
			int* new_container = new int[size_];
			for (int i = 0; i < index_of_empty_element_ + 1; i++) {
				new_container[i] = container_[i];
			}
			delete[]container_;
			container_ = new_container;
		}



		return ret_val;
	}
	bool is_empty()
	{
		bool to_return = index_of_empty_element_ == 0;
		return to_return;
	}

};

//перевірити стек is_empty, повернути true якщо все ок
bool stack_test1()
{
	bool test_passed = true;
	IntStack stack1;
	test_passed = test_passed && stack1.is_empty() == true;
	stack1.push(5);
	test_passed = test_passed && stack1.is_empty() == false;
	stack1.pop();
	test_passed = test_passed && stack1.is_empty() == true;
	return test_passed;
}

//перевірити стек push pop, повернути true якщо все ок
bool stack_test2()
{
	bool test_passed = true;
	IntStack stack1;
	stack1.push(3);
	stack1.push(2);
	test_passed = test_passed && stack1.pop() == 2;
	test_passed = test_passed && stack1.pop() == 3;
	return test_passed;
}
//how size works
bool stack_test3() {
	bool test_passed = true;
	IntStack stack1;
	stack1.push(5);
	stack1.push(1);
	test_passed = test_passed && stack1.getSize() == 2;
	stack1.pop();
	test_passed = test_passed && stack1.getSize() == 1;
	return test_passed;
}
//pop when empty
bool stack_test4() {
	bool test_passed = true;
	IntStack stack1;
	stack1.push(5);
	test_passed = test_passed && stack1.pop() == 5;
	test_passed = test_passed && stack1.pop() == NULL;
	return test_passed;
}
int main()
{
	stack<int> s;
	s.push(10);
	s.push(8);
	s.pop();
	cout << s.top() << endl;
	cout << s.top() << endl;
	s.pop();
	cout << s.empty() << endl;


	cout << "Stack program" << endl;
	cout << "Test 1:" << (stack_test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (stack_test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (stack_test3() ? "passed" : "failed") << endl;
	cout << "Test 4:" << (stack_test4() ? "passed" : "failed") << endl;

	return 0;
}