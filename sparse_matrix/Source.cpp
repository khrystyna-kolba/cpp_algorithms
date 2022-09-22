#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class SparseMatrix {
private:
	size_t n_rows;
	size_t n_cols;
	size_t num_of_el=0; //number of non zero elements
	size_t* rows;
	size_t* cols;
	T* values;
public:
	SparseMatrix(size_t row=0, size_t col=0): n_rows(row),n_cols(col) {
		rows = nullptr;
		cols = nullptr;
		values = nullptr;
	}
	~SparseMatrix() {
		delete[]rows;
		delete[]cols;
		delete[]values;
	}
	SparseMatrix(const SparseMatrix& x) {
		if (this == &x)return;
		n_cols = x.n_cols;
		n_rows = x.n_rows;
		num_of_el = x.num_of_el;
		if (num_of_el == 0) {
			rows = nullptr;
			cols = nullptr;
			values = nullptr;
			return;
		}
		rows = new size_t[num_of_el];
		cols = new size_t[num_of_el];
		values = new T[num_of_el];
		for (int i = 0; i < num_of_el; i++) {
			rows[i] = x.rows[i];
			cols[i] = x.cols[i];
			values[i] = x.values[i];
		}

	}

	SparseMatrix& operator=(const SparseMatrix& x) {
		if (this == &x)return *this;
		n_cols = x.n_cols;
		n_rows = x.n_rows;
		num_of_el = x.num_of_el;
		if (num_of_el == 0) {
			rows = nullptr;
			cols = nullptr;
			values = nullptr;
			return *this;
		}
		rows = new size_t[num_of_el];
		cols = new size_t[num_of_el];
		values = new T[num_of_el];
		for (int i = 0; i < num_of_el; i++) {
			rows[i] = x.rows[i];
			cols[i] = x.cols[i];
			values[i] = x.values[i];
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, SparseMatrix a) {
		int i = 0;
		if (a.num_of_el == 0) {
			for (int j = 0; j < a.n_rows; j++) {
				for (int k = 0; k < a.n_cols; k++) {
					os << 0 << " ";
				}
				os << endl;
			}
			return os;
		}
		a.sort_sparse_matrix();
		for (int j = 0; j < a.n_rows; j++) {
			for (int k = 0; k < a.n_cols; k++) {
				if (a.rows[i] == j && a.cols[i] == k) {
					os << a.values[i] << " ";
					if (i < a.num_of_el - 1)i++;
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
		a.num_of_el = 0;
		for (int i = 0; i < a.n_rows; i++) {
			for (int j = 0; j < a.n_cols; j++) {
				is >> temp_el;
				if (temp_el!=0) {
					a.add_element(i, j, temp_el);
				}
			}
		}
		return is;
	}
	void show_sparse_matrix(ostream& os) {
		int i = 0;
		if (num_of_el == 0) {
			for (int j = 0; j < n_rows; j++) {
				for (int k = 0; k < n_cols; k++) {
					os << 0 << " ";
				}
				os << endl;
			}
			return;
		}
		this->sort_sparse_matrix();
		for (int j = 0; j < n_rows; j++) {
			for (int k = 0; k < n_cols; k++) {
				if (rows[i] == j && cols[i] == k) {
					os << values[i]<<" ";
					if(i<num_of_el-1)i++;
					continue;
				}
				os << 0 << " ";
			}
			os << endl;
		}
}

	T get(size_t row, size_t col) const{
		size_t index;
		bool check_existence = false;
		for (int i = 0; i < num_of_el; i++) {
			if (rows[i] == row && cols[i] == col) {
				index = i;
				check_existence = true;
			}
		}
		if (check_existence) {
			return values[index];
		}
		return 0;
	}

	void sort_sparse_matrix() {
		if (num_of_el == 0)return;
		for (int i = 0; i < num_of_el - 1; i++) {
			for (int j = 0; j < num_of_el - i - 1; j++) {
				if (rows[j] > rows[j + 1]) {
					swap(rows[j], rows[j + 1]);
					swap(cols[j], cols[j + 1]);
					swap(values[j], values[j + 1]);
				}
			}
		}
		for (int i = 0; i < num_of_el - 1; i++) {
			for (int j = 0; j < num_of_el - i - 1; j++) {
				if (rows[j] == rows[j + 1]&& cols[j] > cols[j + 1]) {
					swap(rows[j], rows[j + 1]);
					swap(cols[j], cols[j + 1]);
					swap(values[j], values[j + 1]);
				}
			}
		}
	}
	void sort_sparse_matrix_cols() {
		for (int i = 0; i < num_of_el - 1; i++) {
			for (int j = 0; j < num_of_el - i - 1; j++) {
				if (cols[j] > cols[j + 1]) {
					swap(rows[j], rows[j + 1]);
					swap(cols[j], cols[j + 1]);
					swap(values[j], values[j + 1]);
				}
			}
		}
		for (int i = 0; i < num_of_el - 1; i++) {
			for (int j = 0; j < num_of_el - i - 1; j++) {
				if (cols[j] == cols[j + 1] && rows[j] > rows[j + 1]) {
					swap(rows[j], rows[j + 1]);
					swap(cols[j], cols[j + 1]);
					swap(values[j], values[j + 1]);
				}
			}
		}
	}
	size_t get_num_of_rows(){
		return n_rows;
	}
	size_t get_num_of_columns(){
		return n_cols;
	}
	size_t get_num_of_non_zero_elem() {
		return num_of_el;
	}
	void add_element(size_t row,size_t col, T value) {
		if (row > n_rows-1 || col > n_cols-1) {
			throw invalid_argument("invalid indexes");
		}
		if (value == 0) {
			return;
		}
		size_t* new_rows = new size_t[num_of_el+1];
		size_t* new_cols = new size_t[num_of_el+1];
		T* new_values = new T[num_of_el+1];

		for (int i = 0; i < num_of_el; i++) {
			new_rows[i] = rows[i];
			new_cols[i] = cols[i];
			new_values[i] = values[i];
		}
		delete[]rows;
		delete[]cols;
		delete[]values;

		rows = new_rows;
		cols = new_cols;
		values = new_values;

		rows[num_of_el] = row;
		cols[num_of_el] = col;
		values[num_of_el] = value;

		num_of_el++;
	}
	void remove_element(size_t row, size_t col) {
		if (num_of_el == 0) {
			cout << "sparse matrix doesnt include non null elements" << endl;
			return;
		}


		size_t index;
		bool check_existence = false;
		for (int i = 0; i < num_of_el; i++) {
			if (rows[i] == row && cols[i] == col) {
				index = i;
				check_existence = true;
				break;
			}
		}

		if (!check_existence) {
			cout << "this element is already 0" << endl;
			return;
		}


		num_of_el--;
		for (int i = index; i < num_of_el; i++) {
			rows[i] = rows[i+1];
			cols[i] = cols[i+1];
			values[i] = values[i+1];
		}

	
	}
	SparseMatrix operator*(const SparseMatrix& x) {
		if (this->n_cols != x.n_rows) {
			throw invalid_argument("impossible to multiply matrixes");
		}
		if (this->num_of_el == 0 || x.num_of_el == 0) {
			return SparseMatrix(n_rows, x.n_cols);
		}
		this->sort_sparse_matrix();
		int index_of_row_i=rows[0];
		T temp_res=0;
		vector<size_t> temp_row;
		SparseMatrix res(n_rows, x.n_cols);
		for (int i= 0; i < num_of_el; i++) {
			if (index_of_row_i == rows[i]) {
				temp_row.push_back(i);
			}
			else {
				for (int m = 0; m < x.n_cols;m++) {
					temp_res = 0;
					for (auto k : temp_row) {
						temp_res += x.get(cols[k], m) * values[k];
					}
					if (temp_res != 0) {
						res.add_element(index_of_row_i, m,temp_res);
					}
				}
				temp_row.clear();
				temp_row.push_back(i);
				index_of_row_i = rows[i];
			}
		}
		for (int m = 0; m < x.n_cols;m++) {
			temp_res = 0;
			for (auto k : temp_row) {
				temp_res += x.get(cols[k], m) * values[k];
			}
			if (temp_res != 0) {
				res.add_element(index_of_row_i, m,temp_res);
			}
		}

		return res;
	}
	SparseMatrix operator+(const SparseMatrix& x) {
		if (this->n_cols != x.n_cols||this->n_rows!=x.n_rows){
			throw invalid_argument("impossible to add matrixes");
		}
		if (this->num_of_el == 0) {
			return x;
		}
		else if (x.num_of_el == 0) {
			return *this;
		}
		this->sort_sparse_matrix();
		T t_res;
		SparseMatrix res(n_rows, n_cols);
		for (int i = 0; i < num_of_el; i++) {
			t_res = values[i] + x.get(rows[i], cols[i]);
			if (t_res!=0) {
				res.add_element(rows[i], cols[i], t_res);
			}
		}

		return res;
	}
	SparseMatrix operator-(const SparseMatrix& x) {
		if (this->n_cols != x.n_cols || this->n_rows != x.n_rows) {
			throw invalid_argument("impossible to add matrixes");
		}
		if (this->num_of_el == 0) {
			return x;
		}
		else if (x.num_of_el == 0) {
			return *this;
		}
		this->sort_sparse_matrix();
		T t_res;
		SparseMatrix res(n_rows, n_cols);
		for (int i = 0; i < num_of_el; i++) {
			t_res = values[i] - x.get(rows[i], cols[i]);
			if (t_res != 0) {
				res.add_element(rows[i], cols[i], t_res);
			}
		}

		return res;
	}

};

//how default constructor works
bool test1()
{
	bool test_passed = true;
	SparseMatrix<int> x(2, 3);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			test_passed = test_passed && x.get(i,j) == 0;
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

	z = x * y;
	test_passed = test_passed && z.get(1, 1) == 15;
	return test_passed;
}


int main() {
	cout << "SparseMatrix program" << endl;
	cout << "Test 1:" << (test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (test3() ? "passed" : "failed") << endl;
	cout << "Test 4:" << (test4() ? "passed" : "failed") << endl;





	SparseMatrix<double> x(2, 3);
	cin >> x;
	cout << x;
	return 0;
	SparseMatrix<double> y(2, 3);
	SparseMatrix<double> z(2,3);

	x.add_element(0, 0, 2);
	x.add_element(0, 1, 1);
	x.add_element(0, 2, 4);
	x.add_element(1, 1, 1);
	x.add_element(1, 2, 1);

	y.add_element(0, 0, 6);
	y.add_element(0, 1, 3);
	y.add_element(1, 2, -1);
	

	x.show_sparse_matrix(cout);
	cout << endl;
	y.show_sparse_matrix(cout);


	cout << endl;

	//z = x - y;
	z.show_sparse_matrix(cout);
	cout << z << endl;
	cout << x << endl;
}