#include<iostream>
#include<queue>
using namespace std;
template <typename T>
class Queue {
private:
	class Node {
	public:
		T data;
		Node* prev;
		Node* next;
		Node(T data, Node* prev = nullptr, Node* next = nullptr) :
			data(data), prev(prev), next(next) {}
		~Node() {
			if (this != nullptr) delete prev;
		}
	};
	size_t size_;
	Node* head_;
	Node* tail_;
public:
	Queue() {
		tail_ = head_ =  nullptr;
		size_ = 0;
	}
	/*Queue(const Queue& x) {
		size_=0;
		tail_ = head_ = nullptr;
		if (x.size_ != 0) {
			Node* cur = x.head_;
			this->push(cur->data);
			while (cur->next != nullptr) {
				this->push(cur->data);
				cur = cur->next;
			}
		}
	}
	Queue& operator=(const Queue& x) {
		size_ = 0;
		tail_ = head_ = nullptr;
		if (x.size_ != 0) {
			Node* cur = x.head_;
			this->push(cur->data);
			while (cur->next != nullptr) {
				this->push(cur->data);
				cur = cur->next;
			}
		}
		return *this;
	}*/
	~Queue() {
		if (size_ != 0)delete tail_;
	}
	void push(T data) {
		if (size_ == 0) {
			head_ = tail_ = new Node(data);
			size_++;
			return;
		}
		tail_->next = new Node(data);
		tail_->next->prev = tail_;
		tail_ = tail_->next;
		size_++;
	}
	bool is_empty() {
		return size_ == 0;
	}
	size_t size() {
		return size_;
	}
	T front() {
		if (is_empty()) {
			throw out_of_range("queque is empty");
		}
		return head_->data;
		
	}
	T back() {
		if (is_empty()) {
			throw out_of_range("queque is empty");
		}
		return tail_->data;

	}
	void pop() {
		try{
			front();
			Node* to_del = head_;
			head_ = head_->next;
			if(head_!=nullptr) head_->prev = nullptr;
			delete to_del;
			size_--;
		}
		catch (out_of_range& x) {
			cout << x.what() << endl;
		}

	}
	
};
 //how size works
bool test1()
{
	bool test_passed = true;
	Queue<int> test;
	test_passed = test_passed && test.size() == 0;
	test.push(5);
	test_passed = test_passed && test.size() == 1;
	test.pop();
	test_passed = test_passed && test.size() == 0;
	return test_passed;
}
//push pop front 
bool test2()
{
	bool test_passed = true;
	Queue<int> test;
	test.push(5);
	test_passed = test_passed && test.front() == 5;
	test.push(4);
	test_passed = test_passed && test.front() == 5;
	test.pop();
	test_passed = test_passed && test.front() == 4;
	return test_passed;
}
//back
bool test3()
{
	bool test_passed = true;
	Queue<int> test;
	test.push(5);
	test_passed = test_passed && test.back() == 5;
	test.push(4);
	test_passed = test_passed && test.back() == 4;
	test.pop();
	test_passed = test_passed && test.back() == 4;
	return test_passed;
}


//template <typename T>
//class PriorityQueue {
//private:
//	struct q_el {
//		Queue<T> q;
//		size_t priority;
//		q_el(size_t p = 1, Queue<T> qu = Queue<T>()) :q(qu), priority(p) {}
//		bool operator<(const q_el& x) {
//			return priority < x.priority;
//		}
//		bool operator>(const q_el& x) {
//			return priority > x.priority;
//		}
//	};
//	vector<q_el> queues;
//	size_t size_;
//public:
//	PriorityQueue() {
//		size_ = 0;
//	}
//
//	void push(T data, size_t priority) {
//		for (auto& x : queues) {
//			if (x.priority == priority) {
//				x.q.push(data);
//				size_++;
//				return;
//			}
//
//		}
//		q_el element(priority);
//		element.q.push(data);
//		queues.push_back(element);
//		size_++;
//		sort(queues.begin(), queues.end());
//	}
//	bool is_empty() {
//		return size_ == 0;
//	}
//	size_t size() {
//		return size_;
//	}
//	T front() {
//		if (size_ == 0) {
//			throw out_of_range("queque is empty");
//		}
//		for (auto& x : queues) {
//			if (x.q.size() != 0) {
//				return x.q.front();
//			}
//		}
//	}
//	T back() {
//		if (size_ == 0) {
//			throw out_of_range("queque is empty");
//		}
//		for (int i = queues.size() - 1; i >= 0; i--) {
//			if (queues[i].q.size() != 0) {
//				return queues[i].q.back();
//			}
//		}
//	}
//	void pop() {
//		try {
//			front();
//			for (auto& x : queues) {
//				if (x.q.size() != 0) {
//					x.q.pop();
//					break;
//				}
//			}
//			size_--;
//		}
//		catch (out_of_range& x) {
//			cout << x.what() << endl;
//		}
//
//	}
//
//};

template <typename T>
class PriorityQueue {
private:
	class Node {
	public:
		T data;
		size_t priority;
		Node* prev;
		Node* next;
		Node(T data, size_t priority=0, Node* prev = nullptr, Node* next = nullptr) :
			data(data),priority(priority), prev(prev), next(next) {}
		~Node() {
			if (this != nullptr) delete prev;
		}
	};
	size_t size_;
	Node* head_;
	Node* tail_;
public:
	PriorityQueue() {
		tail_ = head_ = nullptr;
		size_ = 0;
	}
	/*PriorityQueue(const PriorityQueue& x) {
		size_ = 0;
		tail_ = head_ = nullptr;
		if (x.size_ != 0) {
			Node* cur = x.head_;
			this->push(cur->data);
			while (cur->next != nullptr) {
				this->push(cur->data);
				cur = cur->next;
			}
		}
	}
	PriorityQueue& operator=(const PriorityQueue& x) {
		size_ = 0;
		tail_ = head_ = nullptr;
		if (x.size_ != 0) {
			Node* cur = x.head_;
			this->push(cur->data);
			while (cur->next != nullptr) {
				this->push(cur->data);
				cur = cur->next;
			}
		}
		return *this;
	}*/
	~PriorityQueue() {
		if (size_ != 0)delete tail_;
	}
	void push(T data, size_t prior) {
		if (size_ == 0) {
			head_ = tail_ = new Node(data, prior);
			size_++;
			return;
		}
		Node* push_after= tail_;
		while (push_after!=nullptr&& prior < push_after->priority) {
			push_after = push_after->prev;
		}
		Node* new_node;
		if (push_after==nullptr) {
			head_->prev= new Node(data, prior);
			new_node = head_->prev;
			new_node->next = head_;
			head_ = new_node;
		}
		else {
			Node* next = nullptr;
			Node* new_node;
			if (push_after->next != nullptr) {
				next = push_after->next;
			}
			push_after->next = new Node(data, prior);
			new_node = push_after->next;
			new_node->prev = push_after;
			new_node->next = next;
			if (push_after == tail_) {
				tail_ = tail_->next;
			}
			if (next != nullptr) {
				next->prev = new_node;
			}
		}
		size_++;
	}
	bool is_empty() {
		return size_ == 0;
	}
	size_t size() {
		return size_;
	}
	T front() {
		if (is_empty()) {
			throw out_of_range("queue is empty");
		}
		return head_->data;

	}
	T back() {
		if (is_empty()) {
			throw out_of_range("queue is empty");
		}
		return tail_->data;

	}
	void pop() {
		try {
			front();
			Node* to_del = head_;
			head_ = head_->next;
			if (head_ != nullptr) head_->prev = nullptr;
			delete to_del;
			size_--;
		}
		catch (out_of_range& x) {
			cout << x.what() << endl;
		}

	}

};

//how size works
bool ptest1()
{
	bool test_passed = true;
	PriorityQueue<int> test;
	test_passed = test_passed && test.size() == 0;
	test.push(5, 2);
	test_passed = test_passed && test.size() == 1;
	test.pop();
	test_passed = test_passed && test.size() == 0;
	return test_passed;
}
//push pop front 
bool ptest2()
{
	bool test_passed = true;
	PriorityQueue<int> test;
	test.push(5, 2);
	test_passed = test_passed && test.front() == 5;
	test.push(4, 1);
	test_passed = test_passed && test.front() == 4;
	test.push(3, 1);
	test_passed = test_passed && test.front() == 4;
	test.pop();
	test_passed = test_passed && test.front() == 3;
	test.pop();
	test_passed = test_passed && test.front() == 5;
	test.push(6, 10);
	test.pop();
	test_passed = test_passed && test.front() == 6;
	return test_passed;
}
//back
bool ptest3()
{
	bool test_passed = true;
	PriorityQueue<int> test;
	test.push(5, 3);
	test_passed = test_passed && test.back() == 5;
	test.push(4, 2);
	test_passed = test_passed && test.back() == 5;
	test.pop();
	test_passed = test_passed && test.back() == 5;
	return test_passed;
}

//how size works
bool stest1()
{
	bool test_passed = true;
	queue<int> test;
	test_passed = test_passed && test.size() == 0;
	test.push(5);
	test_passed = test_passed && test.size() == 1;
	test.pop();
	test_passed = test_passed && test.size() == 0;
	return test_passed;
}
//push pop front 
bool stest2()
{
	bool test_passed = true;
	queue<int> test;
	test.push(5);
	test_passed = test_passed && test.front() == 5;
	test.push(4);
	test_passed = test_passed && test.front() == 5;
	test.pop();
	test_passed = test_passed && test.front() == 4;
	return test_passed;
}
//back
bool stest3()
{
	bool test_passed = true;
	queue<int> test;
	test.push(5);
	test_passed = test_passed && test.back() == 5;
	test.push(4);
	test_passed = test_passed && test.back() == 4;
	test.pop();
	test_passed = test_passed && test.back() == 4;
	return test_passed;
}
int main() {
	cout << "Queue program" << endl;
	cout << "Test 1:" << (test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (test3() ? "passed" : "failed") << endl;


	cout << "PrriorityQueue program" << endl;
	cout << "Test 1:" << (ptest1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (ptest2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (ptest3() ? "passed" : "failed") << endl;

	cout << "STL Queue program" << endl;
	cout << "Test 1:" << (stest1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (stest2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (stest3() ? "passed" : "failed") << endl;

	cout << "STL PriorityQueue program" << endl;
	priority_queue<int> x;
	x.push(69);
	x.push(5);
	x.push(98);
	while (!x.empty()) {
		cout<<x.top()<<" ";
		x.pop();
	}
}