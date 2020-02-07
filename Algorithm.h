#pragma once
#include <cstring>
#include <utility>
#include "TypeTraits.h"
#include "Iterator.h"
#include "Function.h"
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

	template <class RandomAccessIterator, class Distance, class T, typename Compare = less<typename RandomAccessIterator::value_type>>
	inline void __push_heap_aux(RandomAccessIterator first,
		RandomAccessIterator last, Distance*, T*, Compare c);

	template <class RandomAccessIterator, class Distance, class T>
	void __push_heap(RandomAccessIterator first, Distance holeIndex,
		Distance topIndex, T value);
	template <class RandomAccessIterator, class T, class Distance>
	inline void __pop_heap(RandomAccessIterator first,
		RandomAccessIterator last,
		RandomAccessIterator result,
		T value, Distance*);
	template <class RandomAccessIterator, class Distance, class T>
	void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance len, T value);
	template <class RandomAccessIterator, typename Compare = less<typename RandomAccessIterator::value_type>>
	inline void push_heap(RandomAccessIterator first,
		RandomAccessIterator last,Compare c) {
		// 注意，此函式被呼叫时，新元素应已置于底部容器的最尾端。
		
		__push_heap_aux(first, last, distance_type(first),
			value_type(first),c);
	}
	template <class RandomAccessIterator, class Distance, class T, typename Compare = less<typename RandomAccessIterator::value_type>>
	inline void __push_heap_aux(RandomAccessIterator first,
		RandomAccessIterator last, Distance*, T*,Compare c) {
		typedef typename Compare::type type;
		__push_heap(first, Distance((last - first) - 1), Distance(0),
			T(*(last - 1)),type());
		// 以㆖系根据 implicit representation heap 的结构特性：新值必置于底部
		// 容器的最尾端，此即第㆒个洞号：(last-first)–1。
	}
	template <class RandomAccessIterator, class Distance, class T>
	void __push_heap(RandomAccessIterator first, Distance holeIndex,
		Distance topIndex, T value,max_type) {
		Distance parent = (holeIndex - 1) / 2; 
		while (holeIndex > topIndex && *(first + parent) > value) {
			*(first + holeIndex) = *(first + parent); 
			holeIndex = parent; 
			parent = (holeIndex - 1) / 2; 
		} 
		*(first + holeIndex) = value; 
	}
	template <class RandomAccessIterator, class Distance, class T>
	void __push_heap(RandomAccessIterator first, Distance holeIndex,
		Distance topIndex, T value, min_type) {
		Distance parent = (holeIndex - 1) / 2; // 找出父节点
		while (holeIndex > topIndex && *(first + parent) < value) {
			// 当尚未到达顶端，且父节点小于新值（于是不符合 heap 的次序特性）
			// 由于以㆖使用 operator<，可知 STL heap 是㆒种 max-heap（大者为父）。
			*(first + holeIndex) = *(first + parent); // 令洞值为父值
			holeIndex = parent; // percolate up：调整洞号，向㆖提升至父节点。
			parent = (holeIndex - 1) / 2; // 新洞的父节点
		} // 持续至顶端，或满足 heap 的次序特性为止。
		*(first + holeIndex) = value; // 令洞值为新值，完成安插动作
	}
	template <class RandomAccessIterator, class Distance, class T>
	void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance len, T value) {
		Distance topIndex = holeIndex;
		Distance secondChild = 2 * holeIndex + 2; // 洞节点之右子节点
		while (secondChild < len) {
			// 比较洞节点之左右两个子值，然后以 secondChild 代表较大子节点。
			if (*(first + secondChild) < *(first + (secondChild - 1)))
				secondChild--;
			// Percolate down：令较大子值为洞值，再令洞号㆘移至较大子节点处。
			*(first + holeIndex) = *(first + secondChild);
			holeIndex = secondChild;
			// 找出新洞节点的右子节点
			secondChild = 2 * (secondChild + 1);
		}
		if (secondChild == len) { // 没有右子节点，只有左子节点
		// Percolate down：令左子值为洞值，再令洞号㆘移至左子节点处。
			*(first + holeIndex) = *(first + (secondChild - 1));
			holeIndex = secondChild - 1;
		}
		// 将欲调整值填入目前的洞号内。注意，此时肯定满足次序特性。
		// 依侯捷之见，㆘面直接改为 *(first + holeIndex) = value; 应该可以。
		__push_heap(first, holeIndex, topIndex, value);
	}
	template <class RandomAccessIterator>
	inline void make_heap(RandomAccessIterator first,
		RandomAccessIterator last) {
		__make_heap(first, last, value_type(first), distance_type(first));
	}
	// 以㆘这组 make_heap() 不允许指定「大小比较标准」。
	template <class RandomAccessIterator, class T, class Distance>
	void __make_heap(RandomAccessIterator first,
		RandomAccessIterator last, T*,
		Distance*) {
		if (last - first < 2) return; // 如果长度为 0 或 1，不必重新排列。
		Distance len = last - first;
		// 找出第㆒个需要重排的子树头部，以 parent 标示出。由于任何叶节点都不需执行
		// perlocate down，所以有以㆘计算。parent 命名不佳，名为 holeIndex 更好。
		Distance parent = (len - 2) / 2;
		while (true) {
			// 重排以 parent 为首的子树。len 是为了让 __adjust_heap() 判断操作范围
			__adjust_heap(first, parent, len, T(*(first + parent)));
			if (parent == 0) return;
			parent--;
			// 走完根节点，就结束。
			// （即将重排之子树的）头部向前㆒个节点
		}
	}



	template <class RandomAccessIterator, typename Compare = less<typename RandomAccessIterator::value_type>>
	inline void pop_heap(RandomAccessIterator first,
		RandomAccessIterator last,Compare c) {
		__pop_heap_aux(first, last, value_type(first),c);
	}
	template <class RandomAccessIterator, class T, typename Compare = less<typename RandomAccessIterator::value_type>>
	inline void __pop_heap_aux(RandomAccessIterator first,
		RandomAccessIterator last, T*,Compare c) {
		__pop_heap(first, last - 1, last - 1, T(*(last - 1)),
			distance_type(first));
		// 以㆖，根据 implicit representation heap 的次序特性，pop 动作的结果
		// 应为底部容器的第㆒个元素。因此，首先设定欲调整值为尾值，然后将首值调至
		// 尾节点（所以以㆖将迭代器 result 设为 last-1）。然后重整 [first, last-1)，
		// 使之重新成㆒个合格的 heap。
	}
	template <class RandomAccessIterator, class T, class Distance>
	inline void __pop_heap(RandomAccessIterator first,
		RandomAccessIterator last,
		RandomAccessIterator result,
		T value, Distance*) {
		*result = *first; // 设定尾值为首值，于是尾值即为欲求结果，
		// 可由客端稍后再以底层容器之 pop_back() 取出尾值。
		__adjust_heap(first, Distance(0), Distance(last - first), value);
		// 以㆖欲重新调整 heap，洞号为 0（亦即树根处），欲调整值为 value（原尾值）。
	}
}