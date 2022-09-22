#include<iostream>
using namespace std;
template<typename T>
class Set {
private:
	class Node {
	public:
		T data;
		Node* left_child;
		Node* right_child;
		Node() {
			left_child = right_child = nullptr;
		}
		Node(T data_) {
			data = data_;
			left_child = right_child = nullptr;
		}
		~Node(){
			delete left_child;
		    delete right_child;
		}
		void show() {
			cout << data << " ";
			if (left_child != nullptr) {
				left_child->show();
			}

			if (right_child != nullptr) {
				right_child->show();
			}
		}
		void set_data(T data_) {
			data = data_;
		}
		
	};
	void print_u(Node* root, int space)
	{
		// Base case
		if (root == nullptr)
			return;

		// Increase distance between levels
		space += 10;

		// Process right child first
		print_u(root->right_child, space);

		// Print current node after space
		// count
		cout << endl;
		for (int i = 10; i < space; i++)
			cout << " ";
		cout << root->data << "\n";

		// Process left child
		print_u(root->left_child, space);
	}
	Node* delete_u(Node* node, T to_del) {
		if (node == nullptr) {
			return nullptr;
		}
		if (to_del < node->data) {
			node->left_child=delete_u(node->left_child, to_del);
		}
		else if (to_del > node->data) {
			node->right_child=delete_u(node->right_child, to_del);
		}
		//to_del is equal to our node data
		else {
			//1. node hasnt children
			if (node->right_child == nullptr && node->left_child == nullptr) {
				num_of_elem--;
				delete node;
				return nullptr;
			}
			//2. node has one child
			else if (node->right_child == nullptr || node->left_child == nullptr) {
				Node* to_ret;
				if (node->right_child == nullptr) {
					to_ret = node->left_child;
					node->left_child = nullptr;
					delete node;
					num_of_elem--;
					return to_ret;
				}
				else {
					to_ret = node->right_child;
					node->right_child = nullptr;
					delete node;
					num_of_elem--;
					return to_ret;
				}
			}
			//3. node has two children
			else {
				Node* temp = node->right_child;
				while (temp->left_child != nullptr)
					temp = temp->left_child;
				node->data = temp->data;
				node->right_child = delete_u(node->right_child, node->data);
			}
		}

		return node;
	}
	void iterate_union(Node* node) {
		if (node == nullptr) {
			return;
		}
		if (!is_in_set(node->data)) {
			this->add_element(node->data);
		}
		if (node->left_child != nullptr) {
			iterate_union(node->left_child);
		}
		if (node->right_child != nullptr) {
			iterate_union(node->right_child);
		}
		//current node is a leaf 

	}
	void iterate_complement(Node* node) {
		if (node == nullptr) {
			return;
		}
		if (is_in_set(node->data)) {
			this->delete_element(node->data);
		}
		if (node->left_child != nullptr) {
			iterate_complement(node->left_child);
		}
		if (node->right_child != nullptr) {
			iterate_complement(node->right_child);
		}
		//current node is a leaf 
	}
	void iterate_intersection(Node* node, const Set& x) {
		if (node == nullptr) {
			return;
		}
		if (!x.is_in_set(node->data)) {
			this->delete_element(node->data);
			iterate_intersection(root, x);
			return;
		}
		if (node->left_child != nullptr) {
			iterate_intersection(node->left_child, x);
		}
		if (node->right_child != nullptr) {
			iterate_intersection(node->right_child, x);
		}
		//current node is a leaf 
	}





	Node* root;
	size_t num_of_elem;
public:
	Set() {
		num_of_elem = 0;
		root = nullptr;
	}
	~Set() {
		delete root;
	}
	size_t get_cardinality() {
		return num_of_elem;
	}
	void print()
	{
		// Pass initial space count as 0
		print_u(root, 0);
	}
	void show() {
		if (num_of_elem == 0) {
			cout << "empty set" << endl;
			return;
		}
		root->show();
	}
	void add_element(T to_add) {
		if (root == nullptr) {
			root = new Node(to_add);
			num_of_elem++;
			return;
		}
		Node* parent = root;
		while (true) {
			if (to_add < parent->data) {
				if (parent->left_child == nullptr) {
					break;
				}
				parent = parent->left_child;
			}
			else if (to_add > parent->data) {
				if (parent->right_child == nullptr) {
					break;
				}
				parent = parent->right_child;
			}
			else {
				cout << "such element exists" << endl;
				return;
			}
		}

		if (to_add < parent->data) {
			parent->left_child= new Node(to_add);
		}
		else if (to_add > parent->data) {
			parent->right_child = new Node(to_add);
		}
		num_of_elem++;

	}
	void delete_element(T to_del) {
		root = delete_u(root, to_del);
	}
	bool is_in_set(T val)const {
		Node* temp = root;
		while (temp != nullptr) {
			if (val < temp->data) {
				temp = temp->left_child;
			}
			else if (val > temp->data) {
				temp = temp->right_child;
			}
			else {
				return true;
			}
		}
		return false;
	}
	void set_union(const Set& x) {
		iterate_union(x.root);
	}
	void set_rel_complement(const Set& x) {
		iterate_complement(x.root);
	}
	void set_intersection(const Set& x) {
		iterate_intersection(root, x);
	}
};


int main() {

	Set<int> x;
	x.add_element(5);
	//x.add_element(3);
	x.add_element(7);
	//x.add_element(2);
	//x.add_element(6);
	x.add_element(9);
	x.print();
	cout << endl;
	x.show();



	/*Set<int> x;
	x.add_element(5);
	x.add_element(3);
	x.add_element(7);
	x.add_element(6);
	x.add_element(9);
	x.add_element(2);
	x.add_element(12);
	x.add_element(8);
	cout << x.is_in_set(5) << endl;
	x.print2D();
	x.delete_element(20);
	cout << "after deleting: " << endl;
	x.print2D();*/

	//Set<int> x, y;
	//x.add_element(5);
	//x.add_element(3);
	//x.add_element(7);
	//x.add_element(2);
	//x.add_element(6);
	//x.add_element(9);

	//y.add_element(12);
	//y.add_element(6);
	//y.add_element(7);

	////x.set_intersection(y);
	//x.print();
	//cout << endl;
	//x.show();

}