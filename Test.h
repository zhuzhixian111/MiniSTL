#pragma once


#include <iterator>
#include <iostream>
#include <string>

namespace MiniSTL {
	namespace Test {
	
		template<typename T1,typename T2>
		bool container_equal(T1& t1, T2& t2) {
			auto f1 = std::begin(t1), l1 = std::end(t1);
			auto f2 = std::begin(t2), l2 = std::end(t2);
			for (; f1 != l1 && f2 != l2; ++f1, ++f2) {
				if (*f1 != *f2)
					return false;
			}
			return (f1 == l1 && f2 == l2);
		}
	}
}
