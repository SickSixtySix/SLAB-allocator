#ifndef MOCK_ALLOCATOR_H
#define MOCK_ALLOCATOR_H

/**
 * Allocates a slab of size 4096 * 2^order bytes,
 * with the alignment of 4096 * 2^order bytes. order
 * must be within an interval [0; 10] (both bounds
 * included), which means that no more than 4Mb
 * could be allocated at once.
 **/
void *alloc_slab(int order);

/**
 * Releases a slab previously allocated with
 * alloc_slab function.
 **/
void free_slab(void *slab);

#endif