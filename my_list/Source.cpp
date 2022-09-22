#include<iostream>
using namespace std;
template <typename T>
class List {
private:
	class Node {
	public:
		T data;
		Node* prev;
		Node* next;
		Node(T data, Node* prev=nullptr,Node* next=nullptr):
		data(data),prev(prev),next(next){}
		~Node() {
			delete prev;
		}
	};
	unsigned int size_;
	unsigned int cur_index_;
	Node* head_;
	Node* tail_;
	Node* current_node_;
public:
	List(){
		tail_ = nullptr;
		size_ = 0;
		cur_index_ = 0;
	}
	~List() {
		delete tail_;
		/*delete head_;
		current_node_.prev = current_node_.next = nullptr;
		delete current_node_;*/

	}
	void add_element(T data) {
		if (size_ == 0) {
			current_node_= head_ = tail_ = new Node(data);
			cur_index_ += 1;
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
	unsigned int get_size() {
		return size_;
	}
	T get_data() {
		return current_node_->data;
	}
	bool current_is_a_tail() {
		return current_node_ == tail_;
	}
	bool current_is_a_head() {
		return current_node_ == head_;
	}
	void goto_next() {
		if (!current_is_a_tail()) {
			current_node_ = current_node_->next;
			cur_index_++;
		}
	}
	void goto_head() {
		current_node_ = head_;
		cur_index_=1;
	}
	void goto_prev() {
		if (!current_is_a_head()) {
			current_node_ = current_node_->prev;
			cur_index_--;
		}
	}
	unsigned int get_current_index() {
		return cur_index_;
	}
	void delete_current() {
		if (is_empty()) {
			return;
		}
		Node* new_cur=nullptr;
		if (cur_index_ > 1 && cur_index_ < size_) {
			current_node_->next->prev = current_node_->prev;
			current_node_->prev->next = current_node_->next;
			new_cur= current_node_->prev;
		}
		else if (current_is_a_head()) {
			current_node_->next->prev = nullptr;
			new_cur = current_node_->next;
			head_= current_node_->next;
		}
		else if (current_is_a_tail()) {
			current_node_->prev->next = nullptr;
			new_cur = current_node_->prev;
			tail_= current_node_->prev;
			cur_index_--;
		}
		current_node_->next = current_node_->prev = nullptr;
		delete current_node_;
		current_node_ = new_cur;

		size_--;
	}


};

int main() {
	List<int> list;
	list.add_element(1);
	list.add_element(3);
	list.add_element(5);
	cout <<list.get_current_index()<<" "<< list.get_data() << endl;
	list.goto_next();
	cout << list.get_current_index() << " " << list.get_data() << endl;
	list.goto_next();
	cout << list.get_current_index() << " " << list.get_data() <<
		list.current_is_a_tail()<< endl;
	cout << "size : " << list.get_size() << endl;
	list.delete_current();
	cout << list.get_current_index() << " " << list.get_data() <<
		list.current_is_a_tail() << endl;
	cout << "size : " << list.get_size() << endl;
}