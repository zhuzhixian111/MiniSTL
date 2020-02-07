#pragma once
#include "Test.h"
#include "../Priority_queue.h"
#include <queue>
#include <cassert>
namespace MiniSTL {
	namespace Priority_queueTest {
		template<typename T>
		using minip_greater = MiniSTL::Priority_queue<T, MiniSTL::Vector<T>, MiniSTL::greater<T>>;
		template<typename T>
		using minip_less = MiniSTL::Priority_queue<T>;
		template<typename T>
		using stdp_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;
		template<typename T>
		using stdp_less = std::priority_queue<T>;
		template<typename T1, typename T2>
		bool container_equal(T1& t1, T2& t2) {
			if (t1.size() != t2.size())return false;
			while (!t1.empty()) {
				if (t1.top() != t2.top())return false;
				t1.pop();
				t2.pop();
			}
			return true;
		}

		void test1();
		void test2();
		void testall();
		
	}
}