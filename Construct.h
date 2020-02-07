#pragma once
#include <new>
#include "TypeTraits.h"
namespace MiniSTL {
	template <typename T1, typename T2>
	inline void construct(T1* p, const T2&value) {
		new(p) T1(value);
	}
	template <typename T>
	inline void destroy(T *pointer) {
		pointer->~T();
	}
	template <typename ForwardIterator>
	inline void _destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) {
		
	}
	template <typename ForwardIterator>
	inline void _destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
		for (; first < last; ++first) {
			destroy(&*first);
		}
	}
	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last) {
		typedef typename __type_traits<ForwardIterator>::is_POD_type is_POD_type;
		_destroy_aux(first, last, is_POD_type());
	}
	
}


