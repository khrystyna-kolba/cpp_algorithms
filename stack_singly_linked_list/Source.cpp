#include<iostream>
using namespace std;


template <typename T>
class StackOnLinkedList {
private:
    class Node {
    public:
        T data_;
        Node* prev_;
        Node(T new_data, Node* new_prev = nullptr) {
            data_ = new_data;
            prev_ = new_prev;
        }
        ~Node() {
            delete prev_;
        }
    };
    unsigned int size_;
    Node* top_;

public:
    StackOnLinkedList() {
        top_ = nullptr;
        size_ = 0;
    }
    ~StackOnLinkedList() {
        delete top_;
    }
    void push(T new_element) {
        Node* new_node = new Node(new_element, top_);
        top_ = new_node;
        size_++;
    }
    T pop() {
        if (this->is_empty()) {
            cout << "impossible to pop, stack is empty!" << endl;
            return NULL;
        }
        if (size_ == 1) {
            T to_ret = top_->data_;
            size_--;
            return to_ret;
        }
        T to_ret = top_->data_;
        Node* new_top = top_->prev_;
        top_->prev_ = nullptr;
        delete top_;
        top_ = new_top;
        size_--;
        return to_ret;
    }
    bool is_empty() {
        return size_==0;
    }
    unsigned int getSize() {
        return size_;
    }


};



//перевірити стек is_empty, повернути true якщо все ок
bool stack_test1()
{
	bool test_passed = true;
	StackOnLinkedList<int> stack1;
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
    StackOnLinkedList<int> stack1;
	stack1.push(3);
	stack1.push(2);
	test_passed = test_passed && stack1.pop() == 2;
	test_passed = test_passed && stack1.pop() == 3;
	return test_passed;
}
//how size works
bool stack_test3() {
	bool test_passed = true;
    StackOnLinkedList<int> stack1;
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
    StackOnLinkedList<int> stack1;
	stack1.push(5);
	test_passed = test_passed && stack1.pop() == 5;
	test_passed = test_passed && stack1.pop() == NULL;
	return test_passed;
}


int main() {
    StackOnLinkedList<int> steck;
    steck.push(1);
    steck.push(2);
    cout << steck.pop() << endl;
    cout << steck.pop() << endl;
    steck.push(3);
    cout << steck.pop() << endl;
	cout << "Stack program" << endl;
	cout << "Test 1:" << (stack_test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (stack_test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (stack_test3() ? "passed" : "failed") << endl;
	cout << "Test 4:" << (stack_test4() ? "passed" : "failed") << endl;
}