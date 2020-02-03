#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "Algorithm.h"
#include "Iterator.h"
#include "TypeTraits.h"
#include "Allocator.h"
#include "Construct.h"
#include "Uninitialized.h"

#include <iostream>

namespace MiniSTL {
	template <typename T,typename Alloc=allocator<T>>
	class Vector {
	
	private:
		T* start;
		T* finish;
		T* end_of_storage;
		

	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type* iterator;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t different_type;
		typedef const value_type* const_iterator;
		typedef const value_type& const_reference;
		typedef simple_alloc<value_type, Alloc> data_allocator;
		
	public:
		iterator begin() { return start; }
		const_iterator begin()const { return start; }
		iterator end() { return finish; }
		const_iterator end()const { return finish; }
		iterator END_OF_STORAGE() { return end_of_storage; }
		size_type size() const { return size_type(end() - begin()); }
		size_type capacity() const { return size_type(end_of_storage - begin()); }
		bool empty()const { return begin() == end(); }
		//
		Vector():start(0),finish(0),end_of_storage(0){}
		explicit Vector(size_t n);
		Vector(const int n,const value_type value);
		template<typename InputIterator>
		Vector(InputIterator first, InputIterator last);
		Vector(const Vector&v);
	
		//
		reference operator[](size_type n) { return *(begin() + n); }
		reference front() { return *(begin()); }
		reference back() { return *(end() - 1); }
		//
		void Fill_n(const size_type n, const value_type value);
		void fill_initialize(size_type n, const T&value);
		iterator allocate_and_fill(size_type n, const T&x);
		template<typename InputIterator>
		void allocatorCopy(InputIterator first, InputIterator last);
	public:
	//	~Vector();
		
		void push_back(const value_type &x);
		void pop_back();
		iterator insert(iterator pos, const value_type value);
		iterator insert_aux(iterator position, const value_type&x);
		void clear();
		iterator erase(iterator fitst, iterator last);
		iterator erase(iterator position);

		void deallocate() {
			if (capacity() > 0) {
				alloc::deallocate(start, capacity());
			}
		}
		//value_type &operator[](value_type index);
	};
}
namespace MiniSTL {
	template<typename T, typename Alloc>
	inline Vector<T, Alloc>::Vector(size_t n){
		start = dataAllocator::allocate(n);
		MiniSTL::uninitialized_fill_n(start, n, 0);
		finish = end_of_storage = start + n;

	}
	template<typename T, typename Alloc>
	inline Vector<T, Alloc>::Vector(const int n,const value_type value){
		start = data_allocator::allocate(n);
		MiniSTL::uninitialized_fill_n(start, n, value);
		finish = end_of_storage = start + n;
	
	}
	template<typename T, typename Alloc>
	void Vector<T, Alloc>::Fill_n(const size_type n, const value_type value){
		start = dataAllocator::allocate(n);
		MiniSTL::uninitialized_fill_n(start, n, value);
		finish = end_of_storage = start + n;
	}
	template<typename T, typename Alloc>
	inline void Vector<T, Alloc>::fill_initialize(size_type n, const T & value){
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
	template<typename T, typename Alloc>
	inline typename Vector<T,Alloc>::iterator Vector<T, Alloc>::allocate_and_fill(size_type n, const T & x){
		iterator result = alloc::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}
	template<typename T, typename Alloc>
	template<typename InputIterator>
	inline Vector<T, Alloc>::Vector(InputIterator first, InputIterator last){
		allocatorCopy(first, last);
	}
	template<typename T, typename Alloc>
	template<typename InputIterator>
	inline void Vector<T, Alloc>::allocatorCopy(InputIterator first, InputIterator last){
		start = dataAllocator::allocate(last-first);
		finish = MiniSTL::uninitalized_copy(first, last, start);
		end_of_storage = finish;

	}
	template<typename T,typename Alloc>
	void Vector<T, Alloc>::push_back(const value_type &x) {
		if (finish != end_of_storage) {
			construct(finish, x);
			++finish;
		}
		else {
			insert_aux(end(),x);
			
		}

	}
	template<typename T,typename Alloc>
	typename Vector<T,Alloc>::iterator Vector<T, Alloc>::insert_aux(iterator position, const value_type&x) {
		if (finish != end_of_storage) {
			construct(finish, *(finish - 1));
			++finish;
			T x_copy = x;
			std::copy_backward(position, finish - 2, finish - 1);
			*position = x_copy;
		}
		else {
			const size_type old_size = size();
			const size_type len = old_size != 0 ? 2 * old_size : 1;
			iterator new_start = _allocate((ptrdiff_t)len, x);
			
			iterator new_finish = new_start;
			new_finish = MiniSTL::uninitalized_copy(start, position, new_start);
			
			construct(new_finish, x);
			++new_finish;
			new_finish = MiniSTL::uninitalized_copy(position, finish, new_finish);
			destroy(begin(), end());
			deallocate();
//			MiniSTL::dea
		//	alloc::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;;
			end_of_storage = new_start + len;
				
		}
		return position;
	}
	template<typename T, typename Alloc>
	inline void Vector<T, Alloc>::clear(){
		destroy(start, finish);
		finish = start;
	}
	template<typename T, typename Alloc>
	inline typename Vector<T,Alloc>::iterator Vector<T, Alloc>::erase(iterator first, iterator last){
		iterator i = MiniSTL::copy(last, finish, first);
		destroy(i, finish);
		finish = finish - (last - first);
		return first;
	}
	template<typename T, typename Alloc>
	inline typename Vector<T,Alloc>::iterator Vector<T, Alloc>::erase(iterator position){
		if (position + 1 != end())
			copy(position+1, finish, position);
		--finish;
		destroy(finish);
		return position;
	}
	template<typename T, typename Alloc>
	void Vector<T, Alloc>::pop_back() {
		--finish;
		destroy(finish);
	}
	template<typename T, typename Alloc>
	inline typename Vector<T,Alloc>::iterator Vector<T, Alloc>::insert(iterator pos, const value_type value)
	{

		return insert_aux(pos, value);
	}
}

#endif // !_VECTOR_H_

