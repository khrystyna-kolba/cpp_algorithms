#include<iostream>
#include<stack>
#include<chrono>
using namespace std;
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

template<typename T>
class AVL_Tree {
private:
public:
	class Node {
	public:
		T data;
		Node* left_child;
		Node* right_child;
		int height = 1;
		Node() {
			left_child = right_child = nullptr;
		}
		Node(T data_) {
			data = data_;
			left_child = right_child = nullptr;
		}
		~Node() {
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
	private:
	};
	int height(Node* N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}
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
	Node* rightRotate(Node* y)
	{
		Node* x = y->left_child;
		Node* T2 = x->right_child;
		x->right_child = y;
		y->left_child = T2;
		y->height = max(height(y->left_child),
			height(y->right_child)) + 1;
		x->height = max(height(x->left_child),
			height(x->right_child)) + 1;
		return x;
	}
	Node* leftRotate(Node* x)
	{
		Node* y = x->right_child;
		Node* T2 = y->left_child;
		y->left_child = x;
		x->right_child = T2;
		x->height = max(height(x->left_child),
			height(x->right_child)) + 1;
		y->height = max(height(y->left_child),
			height(y->right_child)) + 1;
		return y;
	}
	// Get Balance factor of node N
	int getBalance(Node* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left_child) - height(N->right_child);
	}
	Node* insert(Node* node, int value)
	{   
		if (node == NULL)
			return new Node(value);

		if (value < node->data)
			node->left_child = insert(node->left_child, value);
		else if (value > node->data)
			node->right_child = insert(node->right_child, value);
		else
			return node;

		node->height = 1 + max(height(node->left_child),
			height(node->right_child));

	
		int balance = getBalance(node);

		// Left Left Case
		if (balance > 1 && getBalance(node->left_child) >= 0)
			return rightRotate(node);

		// Right Right Case
		if (balance < -1 && getBalance(node->right_child) <= 0)
			return leftRotate(node);

		// Left Right Case
		if (balance > 1 && getBalance(node->left_child) < 0)
		{
			node->left_child = leftRotate(node->left_child);
			return rightRotate(node);
		}

		// Right Left Case
		if (balance < -1 && getBalance(node->right_child) > 0)
		{
			node->right_child = rightRotate(node->right_child);
			return leftRotate(node);
		}

		return node;
	}
	Node* delete_(Node* node, T to_del) {
		if (node == nullptr) {
			return nullptr;
		}
		if (to_del < node->data) {
			node->left_child = delete_(node->left_child, to_del);
		}
		else if (to_del > node->data) {
			node->right_child = delete_(node->right_child, to_del);
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
				node->right_child = delete_(node->right_child, node->data);
			}
		}
		if (node == NULL)
			return node;
		node->height = 1 + max(height(node->left_child),
			height(node->right_child));
		int balance = getBalance(node);
		// Left Left Case
		if (balance > 1 && getBalance(node->left_child) >= 0)
			return rightRotate(node);
		// Left Right Case
		if (balance > 1 && getBalance(node->left_child) < 0)
		{
			node->left_child = leftRotate(node->left_child);
			return rightRotate(node);
		}
		// Right Right Case
		if (balance < -1 && getBalance(node->right_child) <= 0)
			return leftRotate(node);
		// Right Left Case
		if (balance < -1 && getBalance(node->right_child) > 0)
		{
			node->right_child = rightRotate(node->right_child);
			return leftRotate(node);
		}
		return node;
	}

	Node* root;
	size_t num_of_elem;
public:
	AVL_Tree() {
		num_of_elem = 0;
		root = nullptr;
	}
	~AVL_Tree() {
		delete root;
	}
	void print()
	{
		// Pass initial space count as 0
		print_u(root, 0);
	}
	void show() {
		if (num_of_elem == 0) {
			cout << "empty tree" << endl;
			return;
		}
		root->show();
	}
	size_t size() {
		return num_of_elem;
	}
	T get_root() {
		return root->data;
	}
	Node* get_p_root() {
		return root;
	}
	void add_element(T to_add) {
		num_of_elem++;
		root = insert(root, to_add);
	}
	void delete_element(T to_del) {
		root = delete_(root, to_del);
	}
	bool is_in_tree(T val)const {
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

	class tree_iterator {
	private:
		stack<Node*> q;

	public:
		tree_iterator(Node* root)
		{
			Node* curr = root;
			while (curr != NULL)
				q.push(curr), curr = curr->left_child;
		}
		Node* current()
		{
			return q.top();
		}
		tree_iterator& operator++(int n)
		{
			Node* curr = q.top()->right_child;
			q.pop();
			while (curr != NULL)
				q.push(curr), curr = curr->left_child;
			return *this;
		}
		T operator*()
		{
			return q.top()->data;
		}
		bool is_end()
		{
			return !(q.size());
		}
	};
};
using std::chrono::duration_cast;
using std::chrono::system_clock;
using nanos = std::chrono::nanoseconds;
using micros = std::chrono::microseconds;
using ms = std::chrono::milliseconds;
using sec = std::chrono::seconds;
bool test3()
{
	auto a = system_clock::now();
	bool passed = true;
	int N = 1000000;
	AVL_Tree<int> tree;

	for (int i = 0; i < N; i++)
	{
		//tree.add_element(i);
		tree.is_in_tree(i);
	}

	auto b = system_clock::now();
	cout << duration_cast<ms>(b - a).count() << "ms" << endl;

	return passed;
}
int main() {
	AVL_Tree<int> x;
	x.add_element(5);
	x.add_element(6);
	x.add_element(7);
	x.add_element(8);
	x.add_element(10);
	AVL_Tree<int>::tree_iterator x_it(x.get_p_root());
	for (x_it; !x_it.is_end(); x_it++) {
		cout << *x_it << " ";
	}
	cout << endl;
	x.print();
	cout << (test3() ?"passed" : "failed") << endl;
}