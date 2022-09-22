#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include "D:\\c++uni\\алгоритми і структури даних\\Set\\Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testset
{
	TEST_CLASS(test_set)
	{
	public:
		TEST_METHOD(test_get_cardinality){
			Set<int> x;
			size_t s = 0;
			Assert::AreEqual(s, x.get_cardinality());
			x.add_element(5);
			s = 1;
			Assert::AreEqual(s, x.get_cardinality());
			x.add_element(10);
			s = 2;
			Assert::AreEqual(s, x.get_cardinality());
			x.add_element(10);
			Assert::AreEqual(s, x.get_cardinality());
			x.delete_element(3);
			Assert::AreEqual(s, x.get_cardinality());
			x.delete_element(10);
			s--;
			Assert::AreEqual(s, x.get_cardinality());
			x.delete_element(5);
			s--;
			Assert::AreEqual(s, x.get_cardinality());
		}

		TEST_METHOD(test_add_element) {
			Set<int> x;
			Assert::AreEqual(false, x.is_in_set(6));
			x.add_element(5);
			Assert::AreEqual(true, x.is_in_set(5));
			x.add_element(5);
			Assert::AreEqual(true, x.is_in_set(5));
			x.add_element(7);
			Assert::AreEqual(true, x.is_in_set(7));
		}

		TEST_METHOD(test_delete_element) {
			Set<int> x;
			x.add_element(78);
			x.add_element(6);
			x.add_element(9);
			x.add_element(94);
		
			Assert::AreEqual(true, x.is_in_set(78));
			Assert::AreEqual(true, x.is_in_set(6));
			Assert::AreEqual(true, x.is_in_set(9));
			Assert::AreEqual(true, x.is_in_set(94));

			x.delete_element(5);

			Assert::AreEqual(true, x.is_in_set(78));
			Assert::AreEqual(true, x.is_in_set(6));
			Assert::AreEqual(true, x.is_in_set(9));
			Assert::AreEqual(true, x.is_in_set(94));

			x.delete_element(9);

			Assert::AreEqual(true, x.is_in_set(78));
			Assert::AreEqual(true, x.is_in_set(6));
			Assert::AreEqual(false, x.is_in_set(9));
			Assert::AreEqual(true, x.is_in_set(94));

			x.delete_element(6);
			x.delete_element(78);
			x.delete_element(94);

			Assert::AreEqual(false, x.is_in_set(78));
			Assert::AreEqual(false, x.is_in_set(6));
			Assert::AreEqual(false, x.is_in_set(9));
			Assert::AreEqual(false, x.is_in_set(94));
		}

		TEST_METHOD(test_union) {
			Set<int> x, y;
			x.add_element(5);
			x.add_element(6);
			x.add_element(9);
			x.add_element(12);

			y.add_element(12);
			y.add_element(6);
			y.add_element(7);

			x.set_union(y);

			Assert::AreEqual(true, x.is_in_set(5));
			Assert::AreEqual(true, x.is_in_set(6));
			Assert::AreEqual(true, x.is_in_set(9));
			Assert::AreEqual(true, x.is_in_set(12));
			Assert::AreEqual(true, x.is_in_set(7));
		}

		TEST_METHOD(test_intersection) {
			Set<int> x, y;
			x.add_element(5);
			x.add_element(6);
			x.add_element(9);
			x.add_element(12);

			y.add_element(12);
			y.add_element(6);
			y.add_element(7);

			x.set_intersection(y);

			Assert::AreEqual(true, x.is_in_set(6));
			Assert::AreEqual(true, x.is_in_set(12));
			Assert::AreEqual(false, x.is_in_set(5));
			Assert::AreEqual(false, x.is_in_set(9));
		}

		TEST_METHOD(test_rel_complement) {
			Set<int> x, y;
			x.add_element(5);
			x.add_element(6);
			x.add_element(9);
			x.add_element(12);

			y.add_element(12);
			y.add_element(6);
			y.add_element(7);

			x.set_rel_complement(y);

			Assert::AreEqual(true, x.is_in_set(5));
			Assert::AreEqual(true, x.is_in_set(9));
			Assert::AreEqual(false, x.is_in_set(6));
		}
	};
}
