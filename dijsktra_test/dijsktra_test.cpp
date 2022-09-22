#include "pch.h"
#include "CppUnitTest.h"
#include "D:\\c++uni\\алгоритми і структури даних\\dijsktra_new\\Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
# define INF 0x3f3f3f3f
namespace dijsktratest
{
	TEST_CLASS(dijsktratest)
	{
	public:
		
		TEST_METHOD(graph1)
		{
			WeightedGraph x(8);
			x.add_new_edge(0, 4, 1);
			x.add_new_edge(0, 3, 4);

			x.add_new_edge(1, 5, 2);
			x.add_new_edge(1, 2, 4);
			x.add_new_edge(1, 4, 0);

			x.add_new_edge(2, 5, 1);
			x.add_new_edge(2, 1, 5);
			x.add_new_edge(2, 3, 4);
			x.add_new_edge(2, 5, 3);

			x.add_new_edge(3, 7, 7);
			x.add_new_edge(3, 5, 2);
			x.add_new_edge(3, 2, 6);

			x.add_new_edge(4,3, 0);
			x.add_new_edge(4, 2, 1);
			x.add_new_edge(4, 6, 5);
			x.add_new_edge(4, 3, 2);

			x.add_new_edge(5, 6, 4);
			x.add_new_edge(5, 5, 6);
			x.add_new_edge(5, 1, 2);

			x.add_new_edge(6, 5, 5);
			x.add_new_edge(6, 2, 3);
			x.add_new_edge(6, 4, 7);

			x.add_new_edge(7, 7, 3);
			x.add_new_edge(7, 4, 6);

			Assert::AreEqual(16, x.dijsktra(0, 7));
		}
		TEST_METHOD(graph_0)
		{
			WeightedGraph x(8);
			
			Assert::AreEqual(INF, x.dijsktra(0, 5));
		}
		TEST_METHOD(graph_k3)
		{
			WeightedGraph x(3);
			x.add_new_edge(0, 7, 1);
			x.add_new_edge(0, 12, 2);

			x.add_new_edge(1, 7, 0);
			x.add_new_edge(1, 34, 2);

			x.add_new_edge(2, 12, 0);
			x.add_new_edge(2, 34, 1);

			Assert::AreEqual(19, x.dijsktra(1, 2));

		}
	};

}
