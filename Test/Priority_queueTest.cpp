#include "Priority_queueTest.h"

namespace MiniSTL {
	namespace Priority_queueTest {
		void test1() {
			stdp_less<int> p1;
			minip_less<int> p2;
			assert(MiniSTL::Priority_queueTest::container_equal(p1,p2));
			for (int i = 0; i < 100; i++) {
				p1.push(i);
				p2.push(i);
			}
			assert(MiniSTL::Priority_queueTest::container_equal(p1, p2));
			for (int i = 0; i < p1.size() / 2; i++) {
				p1.pop();
				p2.pop();
			}
			assert(MiniSTL::Priority_queueTest::container_equal(p1, p2));
		}
		void test2() {
			stdp_greater<int> p1;
			minip_greater<int> p2;
			assert(MiniSTL::Priority_queueTest::container_equal(p1, p2));
			for (int i = 0; i < 100; i++) {
				p1.push(i);
				p2.push(i);
			}
			assert(MiniSTL::Priority_queueTest::container_equal(p1, p2));
			for (int i = 0; i < p1.size() / 2; i++) {
				p1.pop();
				p2.pop();
			}
			assert(MiniSTL::Priority_queueTest::container_equal(p1, p2));
			for (int i = 100; i >= 100/2; i--) {
				p1.push(i);
				p2.push(i);
			}
			assert(MiniSTL::Priority_queueTest::container_equal(p1, p2));
		}
		void testall() {
			test1();
			test2();
		}
	}
}