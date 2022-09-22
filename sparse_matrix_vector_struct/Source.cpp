#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class SparseMatrix {
private:
	struct Element
	{
		size_t row;
		size_t column;
		T value;
		Element(size_t r, size_t c, T val):row(r),column(c),value(val){}
	};
	size_t n_rows;
	size_t n_cols;
	vector<Element> elements;
public:
	SparseMatrix(size_t row = 0, size_t col = 0) : n_rows(row), n_cols(col) {
	}

	SparseMatrix(const SparseMatrix& x) {
		if (this == &x)return;
		n_cols = x.n_cols;
		n_rows = x.n_rows;
		for (auto el : x.elements) {
			this->elements.push_back(el);
		}
	}

	SparseMatrix& operator=(const SparseMatrix& x) {
		if (this == &x)return *this;
		n_cols = x.n_cols;
		n_rows = x.n_rows;
		for (auto el : x.elements) {
			this->elements.push_back(el);
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, SparseMatrix a) {
		if (a.elements.size() == 0) {
			for (int j = 0; j < a.n_rows; j++) {
				for (int k = 0; k < a.n_cols; k++) {
					os << 0 << " ";
				}
				os << endl;
			}
			return os;
		}
		a.sort_sparse_matrix();

		int i = 0;
		for (int j = 0; j < a.n_rows; j++) {
			for (int k = 0; k < a.n_cols; k++) {
				if (a.elements[i].row == j && a.elements[i].column == k) {
					os << a.elements[i].value << " ";
					if (i < a.elements.size() - 1)i++;
					continue;
				}
				os << 0 << " ";
			}
			os << endl;
		}
		return os;
	}
	friend istream& operator>>(istream& is, SparseMatrix& a) {
		is >> a.n_rows >> a.n_cols;
		T temp_el;
		for (int i = 0; i < a.n_rows; i++) {
			for (int j = 0; j < a.n_cols; j++) {
				is >> temp_el;
				if (temp_el != 0) {
					a.add_element(i, j, temp_el);
				}
			}
		}
		return is;
	}
	

	T get(size_t row, size_t col) const {
		size_t index;
		bool check_existence = false;
		for (int i = 0; i < elements.size(); i++) {
			if (elements[i].row == row && elements[i].column == col) {
				index = i;
				check_existence = true;
			}
		}
		if (check_existence) {
			return elements[index].value;
		}
		return 0;
	}

	void sort_sparse_matrix() {
		if (elements.size() == 0)return;
		for (int i = 0; i < elements.size() - 1; i++) {
			for (int j = 0; j < elements.size() - i - 1; j++) {
				if (elements[j].row > elements[j + 1].row) {
					swap(elements[j], elements[j + 1]);
				}
			}
		}
		for (int i = 0; i < elements.size() - 1; i++) {
			for (int j = 0; j < elements.size() - i - 1; j++) {
				if (elements[j].row == elements[j+1].row && elements[j].column > elements[j+1].column) {
					swap(elements[j], elements[j + 1]);
				}
			}
		}
	}
	void sort_sparse_matrix_cols() {
		if (elements.size() == 0)return;
		for (int i = 0; i < elements.size() - 1; i++) {
			for (int j = 0; j < elements.size() - i - 1; j++) {
				if (elements[j].column > elements[j + 1].column) {
					swap(elements[j], elements[j + 1]);
				}
			}
		}
		for (int i = 0; i < elements.size() - 1; i++) {
			for (int j = 0; j < elements.size() - i - 1; j++) {
				if (elements[j].column == elements[j + 1].column && elements[j].row > elements[j + 1].row) {
					swap(elements[j], elements[j + 1]);
				}
			}
		}
	}
	size_t get_num_of_rows() {
		return n_rows;
	}
	size_t get_num_of_columns() {
		return n_cols;
	}
	size_t get_num_of_non_zero_elem() {
		return elements.size();
	}
	void add_element(size_t row, size_t col, T value) {
		if (row > n_rows - 1 || col > n_cols - 1) {
			throw invalid_argument("invalid indexes");
		}
		if (value == 0) {
			return;
		}
		Element to_add(row, col, value);
		elements.push_back(to_add);
	}
	void remove_element(size_t row, size_t col) {
		if (elements.size() == 0) {
			cout << "sparse matrix doesnt include non null elements" << endl;
			return;
		}


		size_t index;
		bool check_existence = false;
		for (int i = 0; i < elements.size(); i++) {
			if (elements[i].row == row && elements[i].column == col) {
				index = i;
				check_existence = true;
				break;
			}
		}

		if (!check_existence) {
			cout << "this element is already 0" << endl;
			return;
		}
		elements.erase(elements.begin() + index);

	}
	SparseMatrix operator*( SparseMatrix& x) {
		if (this->n_cols != x.n_rows) {
			throw invalid_argument("impossible to multiply matrixes");
		}
		SparseMatrix result(n_rows, x.n_cols);
		if (elements.size() == 0 || x.elements.size() == 0) {
			return result;
		}
		this->sort_sparse_matrix();
		x.sort_sparse_matrix_cols();
		size_t temp_i=0;
		size_t x_temp_i=0;
		size_t this_row = 0;
		T res = 0;
		for (size_t i = 0; i < n_rows; i++) {

			if (elements[temp_i].row != i) {
				continue;
			}
			this_row = temp_i;
			for (size_t j = 0; j < x.n_cols; j++) {
				x_temp_i = 0;
				if (x.elements[x_temp_i].column != j) {
					continue;
				}
				res = 0;
				temp_i = this_row;
				while (elements[temp_i].row == i && x.elements[x_temp_i].column == j) {
					if (elements[temp_i].column < x.elements[x_temp_i].row) {
						if (temp_i < x.elements.size() - 1)temp_i++;
						else {
							break;
						}
					}
					else if (elements[temp_i].column > x.elements[x_temp_i].row) {
						if (x_temp_i < x.elements.size() - 1)x_temp_i++;
						else {
							break;
						}
					}
					else {
						res += elements[temp_i].value * x.elements[x_temp_i].value;
						if (temp_i < x.elements.size() - 1&& x_temp_i < x.elements.size() - 1) {
							temp_i++;
							x_temp_i++;
						}
						else {
							break;
						}
					}
				}


				if (res != 0) {
					result.add_element(i, j, res);
				}
			}

		}
		return result;
	}
	SparseMatrix operator+(SparseMatrix& x) {
		if (this->n_cols != x.n_rows) {
			throw invalid_argument("impossible to multiply matrixes");
		}
		SparseMatrix result(n_rows, x.n_cols);
		if (elements.size() == 0) {
			return x;
		}
		else if (x.elements.size() == 0) {
			return *this;
		}
		this->sort_sparse_matrix();
		x.sort_sparse_matrix();
		size_t temp_i=0;
		size_t x_temp_i=0;
		while (temp_i != elements.size() && x_temp_i != x.elements.size()) {
			if (elements[temp_i].row == x.elements[x_temp_i].row&& elements[temp_i].column == x.elements[x_temp_i].column) {
				result.add_element(elements[temp_i].row, elements[temp_i].column, elements[temp_i].value + x.elements[x_temp_i].value);
				temp_i++;
				x_temp_i++;
				continue;
			}
			if (elements[temp_i].row == x.elements[x_temp_i].row) {
				if (elements[temp_i].column < x.elements[x_temp_i].column) {
					result.add_element(elements[temp_i].row, elements[temp_i].column, elements[temp_i].value);
					temp_i++;
				}
				else {
					result.add_element(x.elements[x_temp_i].row, x.elements[x_temp_i].column, x.elements[x_temp_i].value);
					x_temp_i++;
				}
			}
			else if (elements[temp_i].row < x.elements[x_temp_i].row) {
				result.add_element(elements[temp_i].row, elements[temp_i].column, elements[temp_i].value);
				temp_i++;
			}
			else {
				result.add_element(x.elements[x_temp_i].row, x.elements[x_temp_i].column, x.elements[x_temp_i].value);
				x_temp_i++;
			}

		}
		
		return result;
	}
	SparseMatrix operator-(SparseMatrix& x) {
		if (this->n_cols != x.n_rows) {
			throw invalid_argument("impossible to multiply matrixes");
		}
		SparseMatrix result(n_rows, x.n_cols);
		if (elements.size() == 0) {
			return x;
		}
		else if (x.elements.size() == 0) {
			return *this;
		}
		this->sort_sparse_matrix();
		x.sort_sparse_matrix();
		size_t temp_i = 0;
		size_t x_temp_i = 0;
		while (temp_i != elements.size() && x_temp_i != x.elements.size()) {
			if (elements[temp_i].row == x.elements[x_temp_i].row && elements[temp_i].column == x.elements[x_temp_i].column) {
				result.add_element(elements[temp_i].row, elements[temp_i].column, elements[temp_i].value - x.elements[x_temp_i].value);
				temp_i++;
				x_temp_i++;
				continue;
			}
			if (elements[temp_i].row == x.elements[x_temp_i].row) {
				if (elements[temp_i].column < x.elements[x_temp_i].column) {
					result.add_element(elements[temp_i].row, elements[temp_i].column, elements[temp_i].value);
					temp_i++;
				}
				else {
					result.add_element(x.elements[x_temp_i].row, x.elements[x_temp_i].column, -x.elements[x_temp_i].value);
					x_temp_i++;
				}
			}
			else if (elements[temp_i].row < x.elements[x_temp_i].row) {
				result.add_element(elements[temp_i].row, elements[temp_i].column, elements[temp_i].value);
				temp_i++;
			}
			else {
				result.add_element(x.elements[x_temp_i].row, x.elements[x_temp_i].column, -x.elements[x_temp_i].value);
				x_temp_i++;
			}

		}

		return result;
	}

};

//how default constructor works
bool test1()
{
	bool test_passed = true;
	SparseMatrix<int> x(2, 3);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			test_passed = test_passed && x.get(i, j) == 0;
		}
	}
	return test_passed;
}
//adding element
bool test2()
{
	bool test_passed = true;
	SparseMatrix<int> x(2, 3);
	x.add_element(0, 1, 5);
	test_passed = test_passed && x.get(0, 1) == 5;
	test_passed = test_passed && x.get(1, 1) == 0;
	return test_passed;
}
//removing element
bool test3()
{
	bool test_passed = true;
	SparseMatrix<int> x(2, 3);
	x.add_element(0, 1, 5);
	test_passed = test_passed && x.get(0, 1) == 5;
	x.remove_element(0, 1);
	test_passed = test_passed && x.get(0, 1) == 0;
	return test_passed;
}
//multyplying matrixes + testing operator= 
bool test4()
{
	bool test_passed = true;
	SparseMatrix<int> x(5, 4);
	SparseMatrix<int> y(4, 3);
	SparseMatrix<int> z;
	x.add_element(1, 1, 5);
	x.add_element(2, 2, 3);

	y.add_element(1, 1, 3);
	cout << x << endl;
	cout << y << endl;
	z = x * y;
	cout << z << endl;
	test_passed = test_passed && z.get(1, 1) == 15;
	return test_passed;
}


int main() {
	cout << "SparseMatrix program" << endl;
	cout << "Test 1:" << (test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (test3() ? "passed" : "failed") << endl;
	cout << "Test 4:" << (test4() ? "passed" : "failed") << endl;

	SparseMatrix<int> x(4, 4);
	SparseMatrix<int> y(4, 4);
	SparseMatrix<int> z;
	x.add_element(1, 0, 2);
	x.add_element(2, 2, 3);

	y.add_element(1, 1, 3);
	y.add_element(2, 2, 5);
	y.add_element(0, 0, 5);
	cout << x << endl;
	cout << y << endl;
	z = x - y;
	cout << z << endl;
}