#pragma once
#include"Construct.h"
#include "TypeTraits.h"
#include "Iterator.h"

namespace MiniSTL {
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, __true_type);
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, __false_type);

	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitalized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
		typedef typename __type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type isPODType;
		return _uninitialized_copy_aux(first, last, result, isPODType());
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
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type) {
		return copy(first, last, result);
	}

	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, __true_type);
	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, __false_type);
	template<typename ForwardIterator, typename T>
	inline void __uninitialized_fill_n_aux(ForwardIterator first, ForwardIterator last, const T &x, __true_type);
	template<typename ForwardIterator, typename T>
	inline void __uninitialized_fill_n_aux(ForwardIterator first, ForwardIterator last, const T &x, __false_type);

	template<typename ForwardIterator,typename T>
	inline void uninitialized_fill_n(ForwardIterator first, ForwardIterator last, const T&x) {
		typedef typename __type_traits<T>::is_POD_type is_POD;
		__uninitialized_fill_n_aux(first, last, x, is_POD());
	}
	template<typename ForwardIterator,typename Size,typename T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T&x) {
		typedef typename __type_traits<T>::is_POD_type is_POD;
		return __uninitialized_fill_n_aux(first, n, x, is_POD());

	}
	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, __true_type) {
		return MiniSTL::fill_n(first, n, x);
	}
	template<typename ForwardIterator,typename Size,typename T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, __false_type) {
		ForwardIterator cur = first;
		for (; n > 0; --n, ++cur) {
			construct(&*cur, x);
		}
		return cur;
	}
	template<typename ForwardIterator,typename T>
	inline void __uninitialized_fill_n_aux(ForwardIterator first, ForwardIterator last, const T &x, __true_type) {
		std::fill(first, last, x);
	}
	template<typename ForwardIterator, typename T>
	inline void __uninitialized_fill_n_aux(ForwardIterator first, ForwardIterator last, const T &x, __false_type) {
		ForwardIterator cur = first;
		for (; cur != last; ++cur) {
			construct(&*cur, x);
		}
	}
}

