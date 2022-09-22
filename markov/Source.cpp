#include<iostream>
using namespace std;

class MyString {
private:
	class Node {
	public:
		char data_;
		Node* next_;
		Node(char new_data, Node* new_next = nullptr) {
			data_ = new_data;
			next_ = new_next;
		}
		~Node() {
			delete next_;
		}
	};
	unsigned int size_ = 0;
	Node* start_;
	Node* last_;
public:
	MyString() {
		start_ = last_ = nullptr;
	}
	MyString(const char str[]) {
		start_ = last_ = nullptr;
		char c = str[0];
		int it = 0;
		while (c != '\0') {
			this->add(c);
			it++;
			c = str[it];
		}
	}
	MyString(const MyString& x) {
		Node* c = x.start_;
		start_ = last_ = nullptr;
		while (c != nullptr) {
			this->add(c->data_);
			c = c->next_;
		}
	}
	MyString& operator=(const MyString& x) {
		if (start_ != nullptr) { 
			delete start_;
		}
		start_ = last_ = nullptr;
		size_ = 0;
		Node* c = x.start_;
		while (c != nullptr) {
			this->add(c->data_);
			c = c->next_;
		}
		return *this;
	}
	~MyString() {
		delete start_;
	}
	string to_string()const {
		Node* it = this->start_;
		string to_ret = "";
		while (it != nullptr) {
			to_ret += (*it).data_;
			it = it->next_;
		}
		return to_ret;
	}
	bool operator==(const MyString& x)const {
		Node* it = this->start_;
		Node* xit = x.start_;
		if (this->size_ == x.size_&&this->size_==0) {
			return true;
		}
		else if (this->size_ == x.size_) {
			while (it != nullptr) {
				if (it->data_ != xit->data_) {
					return false;
				}
				it = it->next_;
				xit = xit->next_;
			}
			return true;
		}
		return false;
	}
	bool operator!=(const MyString& x)const {
		Node* it = this->start_;
		Node* xit = x.start_;
		if (this->size_ == x.size_ && this->size_ == 0) {
			return false;
		}
		else if (this->size_ == x.size_) {
			while (it != nullptr) {
				if (it->data_ != xit->data_) {
					return true;
				}
				it = it->next_;
				xit = xit->next_;
			}
			return false;
		}
		return true;
	}
	int find(const MyString& x) {
		Node* to_find = x.start_;
		Node* our = this->start_;
		if (to_find == nullptr) {
			return -1;
		}
		int pos = -1;
		int count = 0;
		while (our != nullptr) {
			if (pos == -1 && our->data_ == to_find->data_) {
				pos = count;
				to_find = to_find->next_;
				if (to_find == nullptr) {
					return pos;
				}
			}
			else if (our->data_ == to_find->data_) {
				to_find = to_find->next_;
				if (to_find == nullptr) {
					return pos;
				}
			}
			else {
				pos = -1;
				to_find = x.start_;
				if (pos == -1 && our->data_ == to_find->data_) {
					pos = count;
					to_find = to_find->next_;
					if (to_find == nullptr) {
						return pos;
					}
				}

			}

			our = our->next_;
			count++;
		}
		if (pos >= (this->get_size()  - x.get_size())) {
			return -1;
		}
		return pos;

	}
	void insert(int pos, const MyString& x) {
		if (pos == -1) {
			*this = x + *this;
			return;
		}
		if (pos > size_ - 1) {
			throw out_of_range("out of range");
		}
		Node* it = this->start_;
		if (it == nullptr) {
			throw out_of_range("position is undefined");
		}
		Node* xit = x.start_;
		for (int i = 0; i < pos; i++) {
			it = it->next_;
		}
		while (xit != nullptr) {
			this->add(it, xit->data_);
			it = it->next_;
			xit = xit->next_;
		}
	}
	void remove(int pos) {
		if (pos > size_ - 1) {
			throw out_of_range("out of range");
		}
		if (pos == 0 && size_ == 0) {
			throw out_of_range("out of range");
		}
		else if (pos == 0) {
			Node* to_del=start_;
			start_ = start_->next_;
			to_del->next_ = nullptr;
			delete to_del;
			size_--;
			if (size_ == 0) {
				start_ = last_ = nullptr;
			}
			return;
		}
		Node* prev;
		Node* next;
		Node* to_remove = start_;
		for (int i = 0; i < pos - 1; i++) {
			to_remove = to_remove->next_;
		}
		prev = to_remove;
		to_remove = to_remove->next_;
		next = to_remove->next_;
		prev->next_ = next;
		to_remove->next_ = nullptr;
		delete to_remove;
		if (next == nullptr) {
			last_ = prev;
		}
		size_--;
		if (size_ == 0) {
			start_ = last_ = nullptr;
		}
	}
	void remove(const MyString& find) {
		int pos = this->find(find);
		if (pos == -1) {
			return;
		}
		for (int i = 0; i < find.size_; i++) {
			remove(pos);
		}

	}
	void add(Node* add_after, char x) {
		if (add_after == nullptr) {
			Node* old_st = start_;
			start_= new Node(x);
			start_->next_ = old_st;
			size_++;
			return;
		}
		Node* next = add_after->next_;
		add_after->next_ = new Node(x);
		add_after->next_->next_ = next;
		size_++;
	}
	void replace(const MyString& find, const MyString& replace) {
		Node* add_after = start_;
		Node* it = replace.start_;
		int pos = this->find(find);
		if (pos == -1 && find == MyString("")) {
			*this = replace + *this;
			return;
		 }
		else if(pos == -1){
			return;
		}
		this->remove(find);
		if (pos == 0) {
			if (it != nullptr) {
				this->add(nullptr, it->data_);
				add_after= start_;
				it = it->next_;
			}
			while (it != nullptr) {
				this->add(add_after, it->data_);
				add_after = add_after->next_;
				it = it->next_;
			}
			it = add_after = nullptr;
			return;
		}
		for (int i = 0; i < pos - 1; i++) {
			add_after = add_after->next_;
		}
		while (it != nullptr) {
			this->add(add_after, it->data_);
			add_after = add_after->next_;
			it = it->next_;
		}
		it = add_after = nullptr;
	}
	int get_size()const {
		return size_;
	}
	friend ostream& operator<<(ostream& os, const MyString& x) {
		if (x.size_ == 0) {
			return os;
		}
		Node* c = x.start_;
		while (c != nullptr) {
			os << c->data_;
			c = c->next_;
		}
		return os;
	}
	friend istream& operator>>(istream& is, MyString& x) {
		char temp;
		x.start_ = x.last_ = nullptr;
		is.get(temp);
		while (temp != ' ') {
			x.add(temp);
			is.get(temp);
		}
		return is;
	}
	void add(char to_add) {
		if (size_ == 0) {
			start_ = last_ = new Node(to_add);
			size_++;
			return;
		}
		last_->next_ = new Node(to_add);
		last_ = last_->next_;
		size_++;
	}
	friend MyString operator+(const MyString& y, const MyString& x) {
		MyString to_ret = y;
		Node* it = x.start_;
		while (it != nullptr) {
			to_ret.add(it->data_);
			it = it->next_;
		}
		return to_ret;
	}
};


/*
	Алфавіт V = {0, 1, |}. Формули підстановки:

	1)	1 → 0|

	2)	|0 → 0||

	3)	0 → (порожній рядок).

*/
MyString markov_binary(const MyString& rinput) {
	MyString input = rinput;
	cout << input << endl;
	MyString one = "1";
	MyString pzero = "|0";
	MyString zero = "0";
	MyString rone = "0|";
	MyString rpzero = "0||";
	MyString rzero = "";
	while (true) {
		if (input.find(one) != -1) {
			input.replace(one, rone);
			cout << input << endl;
		}
		else if (input.find(pzero) != -1) {
			input.replace(pzero, rpzero);
			cout << input << endl;
		}
		else if (input.find(zero) != -1) {
			input.replace(zero, rzero);
			cout << input << endl;
		}
		else {
			break;
		}
	}
	return input;
}

/*  
    Алфавіт V = { |, *, a, b, c }. Формули підстановки:

    1)	|b → ba|

	2)	ab → ba

	3)	b → (порожній рядок)

	4) *| → b*

	5) * → c

	6) |c → c

	7) ac → c|

	8) c → (порожній рядок).
*/

MyString markov_mult(const MyString& rinput) {
	MyString input = rinput;
	cout << input << endl;
	while (true) {
		if (input.find(MyString("|b")) != -1) {
			input.replace(MyString("|b"), MyString("ba|"));
			cout << input << endl;
		}
		else if (input.find(MyString("ab")) != -1) {
			input.replace(MyString("ab"), MyString("ba"));
			cout << input << endl;
		}
		else if (input.find(MyString("b")) != -1) {
			input.replace(MyString("b"), MyString(""));
			cout << input << endl;
		}
		else if (input.find(MyString("*|")) != -1) {
			input.replace(MyString("*|"), MyString("b*"));
			cout << input << endl;
		}
		else if (input.find(MyString("*")) != -1) {
			input.replace(MyString("*"), MyString("c"));
			cout << input << endl;
		}
		else if (input.find(MyString("|c")) != -1) {
			input.replace(MyString("|c"), MyString("c"));
			cout << input << endl;
		}
		else if (input.find(MyString("ac")) != -1) {
			input.replace(MyString("ac"), MyString("c|"));
			cout << input << endl;
		}
		else if (input.find(MyString("c")) != -1) {
			input.replace(MyString("c"), MyString(""));
			cout << input << endl;
		}
		else {
			break;
		}
	}
	return input;
}
MyString markov_addition(const MyString& rinput) {
	MyString input = rinput;
	cout << input << endl;
	while (true) {
		if (input.find(MyString("+")) != -1) {
			input.replace(MyString("+"), MyString(""));
			cout << input << endl;
		}
		else {
			break;
		}
	}
	return input;
}
MyString markov_substraction(const MyString& rinput) {
	MyString input = rinput;
	cout << input << endl;
	while (true) {
		if (input.find(MyString("|-|")) != -1) {
			input.replace(MyString("|-|"), MyString("-"));
			cout << input << endl;
		}
		else if (input.find(MyString("|-")) != -1) {
			input.replace(MyString("|-"), MyString("|"));
			cout << input << endl;
		}
		else if (input.find(MyString("-")) != -1&&input.get_size()==1) {
			input.replace(MyString("-"), MyString(""));
			cout << input << endl;
		}
		else {
			break;
		}
	}
	return input;
}

int main() {
	try {
		MyString x="|*|||";
		cout << markov_mult(x) << endl;
	}
	catch (exception& x) {
		cout << x.what() << endl;
	}
}