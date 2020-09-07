#include "mock_allocator.h"
#include <malloc.h>

#define SIZE(X) (4096 * (1 << X))

void *alloc_slab(int order) {
	return _aligned_malloc(SIZE(order), SIZE(order));
}

void free_slab(void *slab) {
	_aligned_free(slab);
}