#include "VectorTest.h"

namespace MiniSTL {
	namespace VectorTest {
	
		void test1() {
			stdv<int> v1(20, 10);
			miniv<int> v2(20, 10);
			assert(MiniSTL::Test::container_equal(v1, v2));
		}
		void test2() {
			stdv<int> v1;
			miniv<int> v2;
			for (int i = 0; i < 1e3; i++) {
				v1.push_back(i);
				v2.push_back(i);
			}
			assert(MiniSTL::Test::container_equal(v1, v2));
		}
		void test3() {
			stdv<int> v1;
			miniv<int> v2;
			for (int i = 0; i < 5e2; i++) {
				v1.push_back(i);
				v2.push_back(i);
			}
			for (int i = 0; i < v1.size() / 2; i++) {
				v1.erase(v1.begin());
				v2.erase(v2.begin());
			}
			assert(MiniSTL::Test::container_equal(v1, v2));

			for (int i = 0; i < 1e2; i++) {
				v1.insert(v1.begin(), i);
				v2.insert(v2.begin(), i);
			}
			assert(MiniSTL::Test::container_equal(v1, v2));
		}
		void test4(){
			stdv<int> v1{ 1,2,3,4,5,6,7,8,9 };
			miniv<int> v2{ 1,2,3,4,5,6,7,8,9 };
			assert(MiniSTL::Test::container_equal(v1, v2));
			v1.front() = 0;
			v2.front() = 0;
			v1.back() = 233;
			v2.back() = 233;
			assert(MiniSTL::Test::container_equal(v1, v2));
			v1.insert(v1.begin() + v1.size() / 2, 10);
			v2.insert(v2.begin() + v2.size() / 2, 10);
			assert(MiniSTL::Test::container_equal(v1, v2));
		}
		void test5() {
			stdv<std::string> v1;
			miniv<std::string> v2;
			v1.push_back("hello");
			v2.push_back("hello");
			assert(MiniSTL::Test::container_equal(v1, v2));
			v1.pop_back();
			v2.pop_back();
			assert(MiniSTL::Test::container_equal(v1, v2));
		}
		void test6() {
			stdv<int> v1;
			miniv<int> v2;
			v1.insert(v1.begin(), 0);
			v2.insert(v2.begin(), 0);
			assert(MiniSTL::Test::container_equal(v1, v2));
			v1.insert(v1.end(), 1);
			v2.insert(v2.end(), 1);
			assert(MiniSTL::Test::container_equal(v1, v2));
		}
		void testall() {
			test1();
			test2();
			test3();
			test4();
			test5();
			test6();
		}
	}
	
}