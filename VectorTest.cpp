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
		void testall() {
			test1();
			test2();
			test3();
		}
	}
	
}