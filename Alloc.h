#pragma once
#include <memory>

namespace MiniSTL {

	class alloc {
	private:
		enum {ALIGN=8};
		enum {MAXBYTES=128};
		enum {NFREELISTS=MAXBYTES/ALIGN};

		union obj {
			union obj *free_list_link;
			char client_data[1];
		};
		
	private:
		static size_t ROUND_UP(size_t bytes) {
			return (((bytes)+ALIGN - 1)&~(ALIGN - 1));
		}
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+ALIGN - 1) / ALIGN - 1);
		}
		static void *refill(size_t n);
		static char *chunk_alloc(size_t size, int &nobjs);
		static char *start_free;
		static char *end_free;
		static size_t heap_size;
		static obj *free_list[NFREELISTS];


	public:
		static void *allocate(size_t n);
		static void *deallocate(void *p, size_t n);
		static void *reallocate(void *p, size_t old_sz, size_t new_sz);
		
	};

}

