#pragma once
#include <cstring>
#include <utility>

namespace MiniSTL {
		
	template <class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val) {
		for (; first != last; ++first) {
			if (*first == val)
				break;
		}
		return first;
	}
	template<typename InputIterator>
	void sort(InputIterator first, InputIterator last) {
		if (first >= last) return;
			
	}
}