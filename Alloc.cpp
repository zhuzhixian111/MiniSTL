#include "Alloc.h"

namespace MiniSTL {
	char *alloc::start_free = 0;
	char *alloc::end_free = 0;
	size_t alloc::heap_size = 0;
	alloc::obj *alloc::free_list[alloc::NFREELISTS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	void *alloc::allocate(size_t n) {
		obj *volatile *my_free_list;
		obj *result;
		if (n > (size_t)MAXBYTES) {
			return malloc(n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (result == 0) {
			void *r = refill(ROUND_UP(n));
			return r;
		}
		*my_free_list = result->free_list_link;
		return result;
	}
	void *alloc::deallocate(void *p, size_t n) {
		obj *q = (obj*)p;
		obj *volatile *my_free_list;
		if (n > (size_t)MAXBYTES) {
			free(p);
			return nullptr;
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;

	}
	void *alloc::refill(size_t n) {
		int nobjs = 20;
		char *chunk = chunk_alloc(n, nobjs);
		obj *volatile *my_free_list, *result, *current_obj, *next_obj;
		int i;
		if (1 == nobjs) return chunk;
		my_free_list = free_list + FREELIST_INDEX(n);
		result = (obj*)chunk;
		*my_free_list = next_obj = (obj*)(chunk + n);
		for (i = 1;; i++) {
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if (nobjs - 1 == i) {
				current_obj->free_list_link = 0;
				break;
			}
			else {
				current_obj->free_list_link = next_obj;
			}
		}
		return result;
	}
	char *alloc::chunk_alloc(size_t size, int &nobjs) {
		char *result;
		size_t total_bytes = size * nobjs;
		size_t bytes_left = end_free - start_free;
		if (bytes_left >= total_bytes) {
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else if (bytes_left >= size) {
			nobjs = bytes_left / size;
			total_bytes = size * nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else {
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0) {
				obj *volatile *my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			start_free = (char*)malloc(bytes_to_get);
			if (0 == start_free) {
				int i;
				obj *volatile *my_free_list, *p;
				for (i = size; i <= MAXBYTES; i += ALIGN) {
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (0 != p) {
						*my_free_list = p->free_list_link;
						start_free = (char*)p;
						end_free = start_free + i;
						return (chunk_alloc(size, nobjs));
					}
				}
				end_free = 0;
				start_free = (char*)malloc(bytes_to_get);

			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return (chunk_alloc(size, nobjs));

		}



	}

}