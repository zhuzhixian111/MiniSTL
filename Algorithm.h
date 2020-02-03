#pragma once
#include <cstring>
#include <utility>
#include "TypeTraits.h"
#include "Iterator.h"

namespace MiniSTL {
		
	template <class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val) {
		for (; first != last; ++first) {
			if (*first == val)
				break;
		}
		return first;
	}
	template<typename T>
	inline T* __copy_t(const T* first, const T* last, T* result, __true_type) {
		memmove(result, first, sizeof(T)*(last - first));
		return result + (last - first);
	}
	template<typename T>
	inline T* __copy_t(const T* first, const T* last, T* result, __false_type) {
		return __copy_d(first, last, result, (ptrdiff_t*)0);
	}
	template<typename InputIterator,typename OutputIterator>
	struct __copy_dispatch {
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
			return __copy(first, last, result, MiniSTL::iterator_category(first));
		}
	};
	template<typename T>
	struct __copy_dispatch<T*, T*> {
		T* operator()(T* first, T*last, T*result) {
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_t(first, last, result, t());
		}
	};
	template<typename T>
	struct __copy_dispatch<const T*, T*> {
		T* operator()(const T* first,const  T*last, T*result) {
			
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_t(first, last, result, t());
		}
	};

	template<typename InputIterator, typename OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}
	template<typename InputIterator,typename OutputIterator>
	inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, MiniSTL::input_iterator_tag) {
		for (; first != last; ++result, ++first) {
			*result = *first;
		}
		return result;
	}
	template<typename RandomAccessIterator, typename OutputIterator>
	inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, MiniSTL::random_access_iterator_tag) {
		return __copy_d(first, last, result, distance_type(first));
	}
	template<typename RandomAccessIterator,typename OutputIterator,typename Distance>
	inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*) {
		for (Distance n = last - first; n > 0; --n, ++result, ++first) {
			*result = *first;
		}
		return result;
	}
	template<typename InputIterator>
	void sort(InputIterator first, InputIterator last) {
		if (first >= last) return;
			
	}
	template<typename OutputIterator,typename Size,typename T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
}