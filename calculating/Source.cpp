#include<iostream>
#include<string>
#include<stack>
using namespace std;
int priority(char operation) {
	if (operation == '+' || operation == '-')return 1;
	else if (operation == '*' || operation == '/')return 2;
	else if (operation == '(' || operation == ')')return 0;
	return 0;
}
bool is_operation(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '(' || c == '.');
}
string postfix(string infix) {
	stack<char> temp;
	string result="";

	string temp_result = "(";
	for (auto x = infix.begin(); x != infix.end();){
		if (!is_operation(*x)) {
			temp_result += *x;
		}
		else if (*x=='(') {
			temp.push(*x);
		}
		else if (*x == ')') {
			temp_result += ")";
			if(temp_result!="()")result += temp_result;
			temp_result = "(";
			while (!temp.empty() && temp.top() != '(') {
				result += temp.top();
				temp.pop();
			}
			if (!temp.empty())temp.pop();
		}
		else if (*x == '.') {
			temp_result += ")";
			if (temp_result != "()")result += temp_result;
			temp_result = "(";
			while (!temp.empty()) {
				result += temp.top();
				temp.pop();
			}
		}
		else if (is_operation(*x)) {
			temp_result += ")";
			if (temp_result != "()")result += temp_result;
			temp_result = "(";
			while (!temp.empty()&&priority(temp.top())>=priority(*x)) {
				result += temp.top();
				temp.pop();
			}
			temp.push(*x);
		}
		x++;
	}
	return result+='.';
}
double calculate(int a, int b, char o) {
	if (o == '+') {
		return ((a) + (b ));
	}
	else if (o == '-') {
		return ((a) - (b));
	}
	else if (o == '*') {
		return ((a ) * (b ));
	}
	else if (o == '/') {
		return ((a ) / (b ));
	}
}
double calculate_postfix(string postfix) {
	stack<int> temp;
	string num = "";
	for (auto x = postfix.begin(); x != postfix.end();) {
		if (*x == '(') {
			x++;
			while (*x != ')') {
				num += *x;
				x++;
			}
			temp.push(stoi(num));
			num = "";
		}
		else if (!is_operation(*x)) {
			temp.push(*x-'0');
		}
		else if (*x == '.') {
			return temp.top();
		}
		else if (is_operation(*x)) {
			int b = temp.top();
			temp.pop();
			int a = temp.top();
			temp.pop();
			temp.push(calculate(a,b,*x));
		}
		x++;
	}
	return 0;
}

bool calc_test1()
{
	bool test_passed = true;
	string x="3*(4+5)-(6-2)*4.";
	test_passed = test_passed && postfix(x)=="(3)(4)(5)+*(6)(2)-(4)*-.";
	test_passed = test_passed && calculate_postfix(postfix(x)) == 11;
	return test_passed;
}
bool calc_test2()
{
	bool test_passed = true;
	string x = "3*(4+54)-(6-2)*4.";
	test_passed = test_passed && postfix(x) == "(3)(4)(54)+*(6)(2)-(4)*-.";
	test_passed = test_passed && calculate_postfix(postfix(x)) == 158;
	return test_passed;
}
bool calc_test3()
{
	bool test_passed = true;
	string x = "789/5*6-(3*5).";
	test_passed = test_passed && calculate_postfix(postfix(x)) == 931.8;
	return test_passed;
}

int main() {

	string x = "((32)+2)*5.";
	cout<<calculate_postfix(postfix(x))<<endl;
	cout << "Calculating program" << endl;
	cout << "Test 1:" << (calc_test1() ? "passed" : "failed") << endl;
	cout << "Test 2:" << (calc_test2() ? "passed" : "failed") << endl;
	cout << "Test 3:" << (calc_test2() ? "passed" : "failed") << endl;
}