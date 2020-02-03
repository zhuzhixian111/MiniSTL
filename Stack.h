#pragma once
#include "Deque.h"
namespace MiniSTL {
	template<typename T, typename Sequence = Vector<T>>
	class Stack {
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
	protected:
		Sequence c;
	public:
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }
		void push(const value_type& x) { c.push_back(x); }
		void pop() { c.pop_back(); }
		template <typename T, typename Sequence>
		friend bool operator==(const Stack<T, Sequence>& x, const Stack<T, Sequence>& y)
		{
			return x.c == y.c;
		}
		
		template <typename T, typename Sequence>
		friend bool operator<(const Stack<T, Sequence>& x, const Stack<T, Sequence>& y)
		{
			return x.c < y.c;
		}
	};
	


}
