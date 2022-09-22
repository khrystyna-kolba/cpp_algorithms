#include<iostream>
#include<string>
using namespace std;
struct TableElement{
	string key;
	double height;
	double age;
	string occupation;
};

class Table {
private:
	TableElement* table_;
	unsigned int size_ = 1;
	unsigned int empty_index_=0;
public:
	Table():table_(new TableElement[size_]) {

	}
	~Table() {
		delete[] table_;
	}
	void add_element(string key, double height, double age, string occupation) {
		if (!this->check_if_key_is_valid(key)) {
			cout << "key is not valid" << endl;
			return;
		}
		if (empty_index_ + 1 == size_) {
			size_ = size_ * 2;
			TableElement* new_container = new TableElement[size_ ];
			for (int i = 0; i < empty_index_; i++) {
				new_container[i] = table_[i];
			}
			delete[]table_;
			table_ = new_container;
		}
		table_[empty_index_].key = key;
		table_[empty_index_].height = height;
		table_[empty_index_].age = age;
		table_[empty_index_].occupation = occupation;
		empty_index_++;
	}
	bool check_if_key_is_valid(string key) {
		for (int i = 0; i < this->get_size(); i++) {
			if (table_[i].key == key) {
				return false;
			}
		}
		return true;
	}
	void show_table(ostream& os) {
		os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		os << "     key    " << "\t\theight   " << "\tage " << "\t\toccupation     " << endl;
		os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		for (int i = 0; i < this->get_size(); i++) {
			this->show_by_index(os, i);
			os << endl;
		}
		os << endl;
	}
	void show_by_index(ostream& os, unsigned int index) {
		if (index >= empty_index_||index<0) {
			cout << "invalid index!!!" << endl;
			return;
		}
		//os << table_[index].key << " height: " << table_[index].height << " age: " << table_[index].age << " occupation: " << table_[index].occupation;
		os <<"    "<< table_[index].key << "\t\t" << table_[index].height << "\t\t" << table_[index].age << "\t\t" << table_[index].occupation << "\t";
	}
	void show(ostream& os, string key) {
		int index = get_index_by_key(key);
		if (index >= empty_index_||index<0) {
			cout << "invalid index!!!" << endl;
			return;
		}
		//os << table_[index].key << " height: " << table_[index].height << " age: " << table_[index].age << " occupation: " << table_[index].occupation;
		os << "    " << table_[index].key << "\t\t" << table_[index].height << "\t\t" << table_[index].age << "\t\t" << table_[index].occupation << "\t";
	}
	void remove_by_index(unsigned int index) {
		if (index >= empty_index_) { 
			cout << "invalid index" << endl;
			return; }
		for (int i = index; i < this->get_size()-1; i++) {
			table_[i] = table_[i + 1];
		}
		empty_index_--;
	}
	void remove_element(string key) {
		int index = get_index_by_key(key);
		if (index >= empty_index_) {
			cout << "invalid index" << endl;
			return;
		}
		for (int i = index; i < this->get_size() - 1; i++) {
			table_[i] = table_[i + 1];
		}
		empty_index_--;
	}
	unsigned int get_index_by_key(string key) {
		for (int i = 0; i < this->get_size(); i++) {
			if (table_[i].key == key) {
				return i;
			}
		}
		return -1;
	}
	string get_occupation(string key) {
		int index = get_index_by_key(key);
		return table_[index].occupation;
	}
	double get_height(string key) {
		int index = get_index_by_key(key);
		return table_[index].height;
	}
	double get_age(string key) {
		int index = get_index_by_key(key);
		return table_[index].age;
	}
	unsigned int get_size() {
		return empty_index_;
	}

};

bool table_test1()
{
	bool test_passed = true;
	Table students;
	test_passed = test_passed && students.get_size() == 0;
	students.add_element("Khrystyna", 175, 17, "student");
	test_passed = test_passed && students.get_size() == 1;
	students.remove_element("Khrystyna");
	test_passed = test_passed && students.get_size() == 0;
	return test_passed;
}
bool table_test2()
{
	bool test_passed = true;
	Table students;
	students.add_element("Whoisthis", 168, 18, "designer");
	test_passed = test_passed && students.get_height("Whoisthis") == 168;
	students.remove_by_index(students.get_index_by_key("Whoisthis"));
	test_passed = test_passed && students.get_size() == 0;
	return test_passed;
}
bool table_test3()
{
	bool test_passed = true;
	Table students;
	students.add_element("Whoisthis", 168, 18, "designer");
	cout << "Waiting for invalid index:   " << endl;
	students.remove_element("Khrystyna");
	cout << "Waiting for Whoisthis 168 18 designer:   " << endl;
	students.show(cout, "Whoisthis");
	cout << endl;
	return test_passed;
}

int main() {
	Table students;
	students.show_table(cout);
	return 0;
	cout << "How does it look like: " << endl;
	students.add_element("Khrystyna", 175, 17, "student");
	students.add_element("Whoisthis", 168, 18, "designer");
	students.add_element("Bodya", 174, 17, "programmer");
	students.show_table(cout);
	cout << "removing Whoisthis..." << endl;
	students.remove_by_index(students.get_index_by_key("Whoisthis"));
	cout << endl;
	students.show_table(cout);
	cout << endl;


	cout << "Table program" << endl;
	cout << "Test 1:" << (table_test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (table_test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (table_test3() ? "passed" : "failed") << endl;
}