#pragma once

#include "Alloc.h"
#include <new>

namespace MiniSTL {

	template<typename T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		//	static T *allocate();
		//	static T *allocate(size_t n);
	
		static T* allocate(size_type n, const void*hint);
		static T* allocate(size_type n);
		static void deallocate(T *ptr);
		static void deallocate(T *ptr, size_t n);

		static void construct(T *ptr);
		static void construct(T *ptr, const T& value);
		static void destroy(T *ptr);
		static void destroy(T *first, T *last);
	};
	template<typename T>
	T *allocator<T>::allocate(size_type n) {
		if (n == 0) return 0;
		return static_cast<T *>(alloc::allocate(sizeof(T) * n));
	}
	template<typename T>
	T* _allocate(ptrdiff_t size, T) {
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0) {

			exit(1);
		}
		return tmp;
	}
	template<typename T>
	T* allocator<T>::allocate(size_type n, const void*hint) {
		return _allocate(difference_type(n), (pointer)0);
	}




	template<typename T>
	void allocator<T>::deallocate(T *ptr) {
		alloc::deallocate(static_cast<void *>(ptr), sizeof(T));
	}
	template<typename T>
	void allocator<T>::deallocate(T *ptr, size_t n) {
		if (n == 0) return;
		alloc::deallocate(static_cast<void *>(ptr), sizeof(T)* n);
	}

	template<typename T>
	void allocator<T>::construct(T *ptr) {
		new(ptr)T();
	}
	template<typename T>
	void allocator<T>::construct(T *ptr, const T& value) {
		new(ptr)T(value);
	}
	template<typename T>
	void allocator<T>::destroy(T *ptr) {
		ptr->~T();
	}
	template<typename T>
	void allocator<T>::destroy(T *first, T *last) {
		for (; first != last; ++first) {
			first->~T();
		}
	}
	template<class T, class Alloc>
	class simple_alloc {
	public:
		static T *allocate(size_t n)
		{
			return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
		}
		static T *allocate(void)
		{
			return (T*)Alloc::allocate(sizeof(T));
		}
		static void deallocate(T *p, size_t n)
		{
			if (0 != n) Alloc::deallocate(p, n * sizeof(T));
		}
		static void deallocate(T *p)
		{
			Alloc::deallocate(p, sizeof(T));
		}
	};
}