#pragma once

#include "Vector.h"
#include <vector>
#include <cassert>
#include "Test.h"

namespace MiniSTL {
	namespace VectorTest {
		template<typename T>
		using stdv = std::vector<T>;
		template<typename T>
		using miniv = MiniSTL::Vector<T>;
		void test1();
		void test2();
		void test3();
		void testall();
	}
}