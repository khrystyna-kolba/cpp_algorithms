#include <iostream>
#include <vector>
#include<stack>
using namespace std;


class SparseMatrix
{
	struct Element
	{
		Element* upper_element = this;
		Element* left_element = this;
		//from 1 to N
		size_t row = 0;
		//from 1 to N
		size_t column = 0;
		double value;
		//but when we are getting or setting values we use well known numeration from 0 to [i]. 
		//numerating from 1 helps us to see the difference between headers and values only.
	};
	size_t rows_count;
	size_t cols_count;
	vector<Element> cols;
	vector<Element> rows;
	
	Element* get_previous_by_row(size_t row, size_t column)
	{
		Element* prev = &rows[row-1];
		while (prev->left_element->column > column)
		{
			prev = prev->left_element;
		}
		return prev;
	}
	Element* get_previous_by_col(size_t row, size_t column)
	{
		Element* prev = &cols[column-1];
		while (prev->upper_element->row > row)
		{
			prev = prev->upper_element;
		}
		return prev;
	}
	//element does not exists
	//add it
	void add_value_impl(Element* previous_by_row, Element* previous_by_col, size_t row, size_t column, double value)
	{
		Element* new_element = new Element();
		new_element->row = row;
		new_element->column = column;
		new_element->value = value;
		new_element->left_element = previous_by_row->left_element;
		previous_by_row->left_element = new_element;
		new_element->upper_element = previous_by_col->upper_element;
		previous_by_col->upper_element = new_element;
	}
	void change_value_impl(Element* previous_by_row, Element* previous_by_col, double value)
	{
		if (value == 0)
		{
			Element* elem_to_del = previous_by_row->left_element;
			previous_by_row->left_element = elem_to_del->left_element;
			previous_by_col->upper_element = elem_to_del->upper_element;
			elem_to_del->left_element = nullptr;
			delete elem_to_del;
		}
		else
		{
			previous_by_row->left_element->value = value;
		}
	}

public:
	SparseMatrix(size_t _rows_count=0, size_t _cols_count=0)
		:rows_count(_rows_count), cols_count(_cols_count)
	{
		cols.resize(cols_count);
		rows.resize(rows_count);
	}
	SparseMatrix(const SparseMatrix& x) {
		if (&x != this) {
			this->rows_count = x.rows_count;
			this->cols_count = x.cols_count;
			cols.resize(cols_count);
			rows.resize(rows_count);
			for (size_t i = 0; i < rows_count; i++) {
				Element* to_add = x.rows[i].left_element;
				while (to_add != &x.rows[i]) {
					this->set_value(to_add->row-1, to_add->column-1, to_add->value);
					to_add = to_add->left_element;
				}
			}
		}
	}
	SparseMatrix& operator=(const SparseMatrix& x) {
		if (&x != this) {
			this->rows_count = x.rows_count;
			this->cols_count = x.cols_count;
			cols.resize(cols_count);
			rows.resize(rows_count);
			for (size_t i = 0; i < rows_count; i++) {
				Element* to_add = x.rows[i].left_element;
				while (to_add != &x.rows[i]) {
					this->set_value(to_add->row-1, to_add->column-1, to_add->value);
					to_add = to_add->left_element;
				}
			}
		}
		return *this;
	}
	~SparseMatrix() {
		Element* last,*to_del;
		for (size_t i = 0; i < rows_count; i++) {
			last = get_previous_by_row(i+1, 0);
			last->left_element = nullptr;
			to_del = rows[i].left_element;
			while (to_del != nullptr) {
				last = to_del;
				to_del = to_del->left_element;
				delete last;
			}
			rows[i].left_element = nullptr;
		}
	}
	friend ostream& operator<<(ostream& os, SparseMatrix& a) {
		stack<Element*> temp_row;
		for (size_t i = 0; i < a.rows_count; i++) {
			Element* current = &a.rows[i];
			if (current->left_element->row != 0) {
				current = current->left_element;
				temp_row.push(current);
				current = current->left_element;
				while (current->row != 0) {
					temp_row.push(current);
					current = current->left_element;
				}
			}
			for (size_t j = 0; j < a.cols_count; j++) {
				if (!temp_row.empty()&&temp_row.top()->column == j+1) {
					os << temp_row.top()->value << " ";
					temp_row.pop();
				}
				else {
					os << 0 << " ";
				}
			}
			os << endl;
		}
		return os;
	}
	friend istream& operator>>(istream& is, SparseMatrix& a) {
		is >> a.rows_count >> a.cols_count;
		a.cols.resize(a.cols_count);
		a.rows.resize(a.rows_count);
		double temp;
		for (size_t i = 0; i < a.rows_count; i++) {
			for (size_t j = 0; j < a.cols_count; j++) {
				cin >> temp;
				if (temp!=0) {
					a.set_value(i+1, j+1, temp);
				}
			}
		}
		return is;
	}
	//set a[row, column]
	//row = 0..row_count-1
	//column = 0..column_count-1
	void set_value(size_t row, size_t column, double value)
	{
		//get element that is previous by row and column
		Element* previous_by_row = get_previous_by_row(row+1, column+1);
		Element* previous_by_col = get_previous_by_col(row+1, column+1);
		//is there element in matrix?
		bool element_in_matrix = previous_by_col->upper_element->row == row+1 &&
			previous_by_col->upper_element->column == column+1;
		if (element_in_matrix)
		{
			change_value_impl(previous_by_row, previous_by_col, value);
		}
		else
		{
			add_value_impl(previous_by_row, previous_by_col, row+1, column+1, value);
		}
	}
	//get a[row, column]
	//row = 0..row_count-1
	//column = 0..column_count-1
	double get_value(size_t row, size_t column)
	{
		double ret_value = 0;
		Element* previous_by_col = get_previous_by_col(row+1, column+1);
		bool element_in_matrix = previous_by_col->upper_element->row == row+1 &&
			previous_by_col->upper_element->column == column+1;
		if (element_in_matrix)
		{
			ret_value = previous_by_col->upper_element->value;
		}
		return ret_value;
	}
	SparseMatrix operator+(SparseMatrix& x) {
		
		if (this->cols_count != x.cols_count || this->rows_count != x.rows_count) {
			throw invalid_argument("impossible to add matrixes");
		}
		//проходиться по елементах кожної з матриць лише один раз*
		SparseMatrix result(x.rows_count,x.cols_count);
		for (size_t i = 0; i < rows_count; i++) {
			Element* cur=rows[i].left_element;
			Element* x_cur = x.rows[i].left_element;
			while (cur->row != 0|| x_cur->row != 0) {
				if (cur->column > x_cur->column) {
					result.set_value(i, cur->column, cur->value);
					cur = cur->left_element;
				}
				else if (cur->column < x_cur->column) {
					result.set_value(i, x_cur->column, x_cur->value);
					x_cur = x_cur->left_element;
				}
				else {
					result.set_value(i, cur->column, cur->value + x_cur->value);
					cur = cur->left_element;
					x_cur = x_cur->left_element;
				}
			}

		}
		return result;
	}
	SparseMatrix operator-(SparseMatrix& x) {

		if (this->cols_count != x.cols_count || this->rows_count != x.rows_count) {
			throw invalid_argument("impossible to substract matrixes");
		}
		//проходиться по елементах кожної з матриць лише один раз*
		SparseMatrix result(x.rows_count, x.cols_count);
		for (size_t i = 0; i < rows_count; i++) {
			Element* cur = rows[i].left_element;
			Element* x_cur = x.rows[i].left_element;
			while (cur->row != 0 || x_cur->row != 0) {
				if (cur->column > x_cur->column) {
					result.set_value(i, cur->column, cur->value);
					cur = cur->left_element;
				}
				else if (cur->column < x_cur->column) {
					result.set_value(i, x_cur->column, -x_cur->value);
					x_cur = x_cur->left_element;
				}
				else {
					result.set_value(i, cur->column, cur->value - x_cur->value);
					cur = cur->left_element;
					x_cur = x_cur->left_element;
				}
			}

		}
		return result;
	}
	SparseMatrix operator*(SparseMatrix& x) {

		if (this->cols_count != x.rows_count) {
			throw invalid_argument("impossible to multiply matrixes");
		}
		
		SparseMatrix result(this->rows_count, x.cols_count);
		Element* temp;
		Element* x_temp;
		double res = 0;
		for (size_t i = 0; i < rows_count; i++) {
			for (size_t j = 0; j < x.cols_count; j++) {
				res = 0;
				temp = rows[i].left_element;
				x_temp = x.cols[j].upper_element;
				while (temp->row != 0 || x_temp->row != 0) {
					if (temp->column > x_temp->row) {
						temp = temp->left_element;
					}
					else if (temp->column < x_temp->row) {
						x_temp = x_temp->upper_element;
					}
					else {
						res += temp->value * x_temp->value;
						temp = temp->left_element;
						x_temp = x_temp->upper_element;
					}
				}
				if (res != 0) {
					result.set_value(i, j, res);
				}
			}

		}
		return result;
	}
	SparseMatrix operator*(vector<double> x) {

		if (this->cols_count != x.size()) {
			throw invalid_argument("impossible to multiply matrix and vector");
		}

		SparseMatrix result(this->rows_count, 1);
		Element* temp;
		double x_temp;
		size_t x_index = x.size()-1;
		double res = 0;
		for (size_t i = 0; i < rows_count; i++) {
				res = 0;
				temp = rows[i].left_element;
				x_index = x.size() - 1;
				x_temp = x[x_index];
				while (temp->row != 0) {
					if (temp->column > x_index+1) {
						temp = temp->left_element;
					}
					else if (temp->column < x_index+1) {
						x_index--;
						x_temp = x[x_index];
					}
					else {
						res += temp->value * x_temp;
						temp = temp->left_element;
						x_index--;
						x_temp = x[x_index];
					}
				}
				if (res != 0) {
					result.set_value(i, 0, res);
				}
			}
		return result;
	}
};




bool test1()
{
	SparseMatrix matr(5, 5);
	matr.set_value(1, 1, 11);
	matr.set_value(3, 2, 32);
	matr.set_value(3, 3, 33);
	matr.set_value(3, 2, 0);
	bool result = matr.get_value(1, 1) == 11;
	result =result&&  matr.get_value(3, 2) == 0;
	result = result && matr.get_value(3, 3) == 33;
	result = result && matr.get_value(4, 2) == 0;
	return result;
}
//multiplying
bool test2() {
	bool result = true;
	SparseMatrix x(5, 4);
	SparseMatrix y(4, 3);
	SparseMatrix z;
	x.set_value(1, 1, 5);
	x.set_value(2, 2, 3);

	y.set_value(1, 1, 3);

	z = x * y;
	result = result && z.get_value(1, 1) == 15;
	return result;
}
//removing element
bool test3()
{
	bool test_passed = true;
	SparseMatrix x(2, 3);
	x.set_value(0, 1, 5);
	test_passed = test_passed && x.get_value(0, 1) == 5;
	x.set_value(0, 1, 0);
	test_passed = test_passed && x.get_value(0, 1) == 0;
	return test_passed;
}

bool test4() {
	bool result = true;
	SparseMatrix z(3, 5);
	z.set_value(1, 1, 5);
	z.set_value(2, 2, 3);
	vector<double> x = { 1,2,3,4,0 };
	SparseMatrix val;
	val = z * x;
	result = result && val.get_value(1, 0) == 10;
	result = result && val.get_value(2, 0) == 9;
	return result;
}
int main()
{
	cout << "SparseMatrix tests" << endl;
	cout << "Test1 " << (test1() ? "passed" : "failed") << endl;
	cout << "Test2 " << (test2() ? "passed" : "failed") << endl;
	cout << "Test3 " << (test3() ? "passed" : "failed") << endl;
	cout << "Test4 " << (test4() ? "passed" : "failed") << endl;

}