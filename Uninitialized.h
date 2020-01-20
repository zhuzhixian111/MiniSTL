#pragma once
#include"Construct.h"
#include "TypeTraits.h"
#include "Iterator.h"

//#include <algorithm>

namespace MiniSTL {
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitalized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, __true_type);
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitalized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, __false_type);

	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitalized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
		typedef typename __type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type isPODType;
		return _uninitalized_copy_aux(first, last, result, isPODType());
		
	}
	template <typename InputIterator, typename ForwardIterator, typename T>
	inline ForwardIterator __uninitalized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*) {
		typedef typename __type_traits<T>::is_POD_type is_POD;
		return __uninitalized_copy_aux(first, last, result, is_POD());
	}
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type) {
		ForwardIterator cur = result;
		for (; first != last; ++first, ++cur) {
			construct(&*cur, *first);
		}
		return cur;
	}
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitalized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type) {
		ForwardIterator cur = result;
		for (; first != last; ++first, ++cur)
			construct(&*cur, *first);
		return cur;
	}
	template<typename ForwardIterator,typename Size,typename T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T&x) {
		//return __uninitialized_fill_n(first, n, x, value_type(first));
		typedef typename __type_traits<T>::is_POD_type is_POD;
		return __uninitialized_fill_n_aux(first, n, x, is_POD());

	}
	template<typename ForwardIterator,class Size,class T,class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T &x, T1*) {
		typedef typename __type_traits<T1>::is_POD_type is_POD;
		return __uninitialized_fill_n_aux(first, n, x, is_POD());
	}
	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, __true_type) {
		ForwardIterator cur = first;
		for (; n > 0; --n, ++cur) {
			construct(&*cur, x);
		}
		return cur;
	}
	template<typename ForwardIterator,typename Size,typename T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, __false_type) {
		ForwardIterator cur = first;
		for (; n > 0; --n, ++cur) {
			construct(&*cur, x);
		}
		return cur;
	}
}

