#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include "D:\\c++uni\\алгоритми і структури даних\\markov\\Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static wstring ToString<MyString>(const MyString& str) {
				string res = str.to_string();
				wstring wstr(res.begin(), res.end());
				return wstr;
			}

		}
	}
}
namespace testmarkov
{
	TEST_CLASS(testmystring)
	{
	public:
		
		TEST_METHOD(Test_operator_plus)
		{
			MyString x = "mam";
			MyString y = "onts";
			MyString b = "";
			Assert::AreEqual(MyString("mamonts"), x+y);
			Assert::AreEqual(x + b, MyString("mam"));
			Assert::AreEqual(b+x, MyString("mam"));
			Assert::AreEqual(b+b, MyString(""));
		}
		TEST_METHOD(Test_get_size)
		{
			MyString x = "mamonts";
			Assert::AreEqual(7, x.get_size());
			x = "";
			Assert::AreEqual(0, x.get_size());
			x.add('f');
			Assert::AreEqual(1, x.get_size());
		}
		TEST_METHOD(Test_insert_method)
		{
			MyString x = "mamonts";
			MyString y = " are cute";
			MyString s = "";
			x.insert(6, y);
			Assert::AreEqual(MyString("mamonts are cute"), x);
			x = "mamonts";
			y = "you are ";
			x.insert(-1, y);
			Assert::AreEqual(MyString("you are mamonts"), x);
			x.insert(3, y);
			Assert::AreEqual(MyString("you you are are mamonts"), x);
		}
		TEST_METHOD(Test_replace_method)
		{
			MyString x = "mamonts";
			MyString y = " are cute";
			y.replace(MyString("are"), x);
			Assert::AreEqual(MyString(" mamonts cute"), y);
		}
	};
	TEST_CLASS(testmarkov)
	{
	public:
		TEST_METHOD(Test_markov_binary)
		{
			MyString x = "101";
			Assert::AreEqual(MyString("|||||"), markov_binary(x));
			x = "";
			Assert::AreEqual(MyString(""), markov_binary(x));
			x = "01";
			Assert::AreEqual(MyString("|"), markov_binary(x));
			x = "10";
			Assert::AreEqual(MyString("||"), markov_binary(x));
			x = "111";
			Assert::AreEqual(MyString("|||||||"), markov_binary(x));
		}
		TEST_METHOD(Test_markov_mult)
		{
			MyString x = "||*|||";
			Assert::AreEqual(MyString("||||||"), markov_mult(x));
			x = "|*||";
			Assert::AreEqual(MyString("||"), markov_mult(x));
			x = "|";
			Assert::AreEqual(MyString("|"), markov_mult(x));
			x = "|*|";
			Assert::AreEqual(MyString("|"), markov_mult(x));
			x = "";
			Assert::AreEqual(MyString(""), markov_mult(x));
			x = "|*0";
			Assert::AreEqual(MyString("0"), markov_mult(x));
		}
		TEST_METHOD(Test_markov_add)
		{
			MyString x = "||+|||";
			Assert::AreEqual(MyString("|||||"), markov_addition(x));
			x = "+||";
			Assert::AreEqual(MyString("||"), markov_addition(x));
			x = "|||+|||";
			Assert::AreEqual(MyString("||||||"), markov_addition(x));
		}
		TEST_METHOD(Test_markov_substr)
		{
			MyString x = "||||-|||";
			Assert::AreEqual(MyString("|"), markov_substraction(x));
			x = "||-||";
			Assert::AreEqual(MyString(""), markov_substraction(x));
			x = "|||-|||||";
			Assert::AreEqual(MyString("-||"), markov_substraction(x));
		}
	};
}
