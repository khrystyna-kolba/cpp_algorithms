#include "pch.h"
#include "CppUnitTest.h"
#include "D:\\c++uni\\алгоритми і структури даних\\AVL_tree\\Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVLtest
{
	TEST_CLASS(AVLtest)
	{
	public:
		
		TEST_METHOD(balancing_decreasing_row)
		{
			AVL_Tree<int> x;
			x.add_element(5);
			x.add_element(6);
			x.add_element(7);
			x.add_element(8);
			Assert::AreEqual(6, x.get_root());
			x.add_element(10);
			Assert::AreEqual(6, x.get_root());
		}
		TEST_METHOD(left_right)
		{
			AVL_Tree<int> x;
			x.add_element(7);
			x.add_element(4);
			x.add_element(5);
			Assert::AreEqual(5, x.get_root());
		}
		TEST_METHOD(right_left)
		{
			AVL_Tree<int> x;
			x.add_element(7);
			x.add_element(10);
			x.add_element(9);
			Assert::AreEqual(9, x.get_root());
		}
		TEST_METHOD(test_is_in_tree)
		{
			AVL_Tree<int> x;
			x.add_element(5);
			x.add_element(6);
			x.add_element(12);
			x.add_element(2);
			Assert::AreEqual(true, x.is_in_tree(6));
			Assert::AreEqual(false, x.is_in_tree(23));
		}
		TEST_METHOD(test_delete)
		{
			AVL_Tree<int> x;
			x.add_element(43);
			x.add_element(19);
			x.add_element(5);
			x.add_element(45);
			x.add_element(5);
			x.add_element(6);
			Assert::AreEqual(true, x.is_in_tree(45));
			x.delete_element(45);
			Assert::AreEqual(false, x.is_in_tree(45));
		}
	};
}
