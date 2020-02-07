#pragma once
namespace MiniSTL {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};
	
	template<typename Category,typename T,typename Distance=ptrdiff_t,typename Pointer=T*,typename Reference=T&>
	struct iterator {
		typedef Category iterator_catrgory;
		typedef T value_type;
		typedef Distance different_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};
	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_catgory;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::different_type different_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;

	};
	
	template <typename T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_catrgory;
		typedef T value_type;
		typedef long long different_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template <typename T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_catrgory;
		typedef T value_type;
		typedef long long different_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::different_type*
	distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::different_type>(0);
	}
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::value_type*
	value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

}