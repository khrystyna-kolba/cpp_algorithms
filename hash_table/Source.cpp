#include<iostream>
#include<string>
using namespace std;

template <typename T>
class List {
private:
	class Node {
	public:
		T data;
		Node* prev;
		Node* next;
		Node(T data, Node* prev = nullptr, Node* next = nullptr) :
			data(data), prev(prev), next(next) {}
		~Node() {
			if(this!=nullptr) delete prev;
		}
	};
	unsigned int size_;
	unsigned int cur_index_;
	Node* head_;
	Node* tail_;
	Node* current_node_;
public:
	List() {
		tail_=head_=current_node_ = nullptr;
		size_ = 0;
		cur_index_ = 0;
	}
	~List() {
		if(size_!=0)delete tail_;
	}
	void add_element(T data) {
		if (size_ == 0) {
			current_node_ = head_ = tail_ = new Node(data);
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
		if(!is_empty())return current_node_->data;
		return NULL;
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
		cur_index_ = 1;
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
		if (is_empty()|| size_ == 1) {
			size_=0;
			delete current_node_;
			current_node_ =head_=tail_ =nullptr;
			return;
		}
		
		Node* new_cur = nullptr;
		if (cur_index_ > 1 && cur_index_ < size_) {
			current_node_->next->prev = current_node_->prev;
			current_node_->prev->next = current_node_->next;
			new_cur = current_node_->prev;
		}
		else if (current_is_a_head()) {
			current_node_->next->prev = nullptr;
			new_cur = current_node_->next;
			head_ = current_node_->next;
		}
		else if (current_is_a_tail()) {
			current_node_->prev->next = nullptr;
			new_cur = current_node_->prev;
			tail_ = current_node_->prev;
			cur_index_--;
		}
		current_node_->next = current_node_->prev = nullptr;
		delete current_node_;
		current_node_ = new_cur;

		size_--;
	}
};





















struct TableElement {
    unsigned int key;
	double height;
	double age;
	string occupation;
	TableElement(int key=0, double he=0, double age=0, string oc="") :key(key), height(he), age(age), occupation(oc) {

	}
};

class HashTable {
private:
	const static int SIZE = 10;
	List<TableElement> table_[SIZE];
	unsigned int num_of_elements = 0;
	int get_hash(int key) {
		if (key == 0) {
			cout << "invalid key" << endl;
			return 0;
		}
		return key % SIZE;
	}
public:
	HashTable(){
	}
	~HashTable() {
		//there are not dynamic fields
	}
	void add_element(int key, double height, double age, string occupation) {
		if (!check_if_key_is_valid(key)) {
			cout << "invalid key" << endl;
			return;
		}
		TableElement new_element(key, height, age, occupation);
		table_[get_hash(key)].add_element(new_element);
		num_of_elements++;
	}
	bool check_if_key_is_valid(int key) {
		for (int i = 0; i < SIZE; i++) {
			if (table_[i].get_size()!=0) {
				while (!table_[i].current_is_a_tail()) {
					if (table_[i].get_data().key == key) {
						return false;
					}
					table_[i].goto_next();
				}
				if (table_[i].get_data().key == key) {
					return false;
				}
				table_[i].goto_head();
			}
		}
		return true;
	}
	void show_table(ostream& os) {
		os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		os << "    key    " << "\theight   " << "\tage " << "\t\toccupation     " << endl;
		os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		for (int i = 0; i < SIZE; i++) {
			if (table_[i].get_size() == 0) continue;
			while (!table_[i].current_is_a_tail()) {
				this->show(os, table_[i].get_data().key);
				table_[i].goto_next();
				os << endl;
			}
			this->show(os, table_[i].get_data().key);
			table_[i].goto_head();
			os << endl;
		}
		os << endl;
	}
	
	void show(ostream& os, int key) {
		int hash = get_hash(key);
		while (key != table_[hash].get_data().key && !table_[hash].current_is_a_tail()) {
			table_[hash].goto_next();
		}
		if (table_[hash].get_data().key != key) {
			cout << "invalid key" << endl;
			return;
		}
		//os << table_[index].key << " height: " << table_[index].height << " age: " << table_[index].age << " occupation: " << table_[index].occupation;
		os << "    " << table_[hash].get_data().key << "\t\t" << table_[hash].get_data().height << "\t\t" << table_[hash].get_data().age << "\t\t" << table_[hash].get_data().occupation << "\t";
	}
	void remove_element(int key) {
		int hash = get_hash(key);
		while (key != table_[hash].get_data().key && !table_[hash].current_is_a_tail()) {
			table_[hash].goto_next();
		}
		if (table_[hash].get_data().key != key) {
			cout << "invalid key" << endl;
			return ;
		}
		table_[hash].delete_current();
		table_[hash].goto_head();
		num_of_elements--;
	}
	string get_occupation(int key) {
		int hash = get_hash(key);
		string to_ret;
		while (key != table_[hash].get_data().key&& !table_[hash].current_is_a_tail()) {
			table_[hash].goto_next();
		}
		if (table_[hash].get_data().key != key) {
			cout << "invalid key" << endl;
			return NULL;
		}
		to_ret = table_[hash].get_data().occupation;
		table_[hash].goto_head();
		return to_ret;

	}
	double get_height(int key) {
		double to_ret;
		int hash = get_hash(key);
		while (key != table_[hash].get_data().key && !table_[hash].current_is_a_tail()) {
			table_[hash].goto_next();
		}
		if (table_[hash].get_data().key != key) {
			cout << "invalid key" << endl;
			return NULL;
		}
		to_ret = table_[hash].get_data().height;
		table_[hash].goto_head();
		return to_ret;
	}
	double get_age(int key) {
		double to_ret;
		int hash = get_hash(key);
		while (key != table_[hash].get_data().key && !table_[hash].current_is_a_tail()) {
			table_[hash].goto_next();
		}
		if (table_[hash].get_data().key != key) {
			cout << "invalid key" << endl;
			return NULL;
		}
		to_ret = table_[hash].get_data().age;
		table_[hash].goto_head();
		return to_ret;
	}
	unsigned int get_size() {
		return num_of_elements;
	}

};

bool table_test1()
{
	bool test_passed = true;
	HashTable students;
	test_passed = test_passed && students.get_size() == 0;
	students.add_element(45, 175, 17, "student");
	test_passed = test_passed && students.get_size() == 1;
	students.remove_element(45);
	test_passed = test_passed && students.get_size() == 0;
	return test_passed;
}
bool table_test2()
{
	bool test_passed = true;
	HashTable students;
	students.add_element(69, 168, 18, "designer");
	test_passed = test_passed && students.get_height(69) == 168;
	students.remove_element(69);
	test_passed = test_passed && students.get_size() == 0;
	return test_passed;
}
bool table_test3()
{
	bool test_passed = true;
	HashTable students;
	students.add_element(54, 168, 18, "designer");
	cout << "Waiting for invalid key:   " << endl;
	students.remove_element(56);
	cout << "Waiting for 54 168 18 designer:   " << endl;
	students.show(cout, 54);
	cout << endl;
	return test_passed;
}
int main() {
	HashTable students;
	students.add_element(440, 168, 18, "designer");
	students.add_element(110, 175, 17, "student");
	students.add_element(230, 150, 50, "artist");
	students.add_element(310, 175, 17, "programmer");
	students.show_table(cout);

	cout << "Table program" << endl;
	cout << "Test 1:" << (table_test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (table_test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (table_test3() ? "passed" : "failed") << endl;
}