#ifndef SLAB_ALLOCATOR_H
#define SLAB_ALLOCATOR_H

#include <stdint.h>

/**
 * Structure of an object within a slab.
 * Objects are arranged via a bi-directional
 * linked list of free objects.
 **/
typedef struct object {
	struct object *prev; /* Pointer to the previous free object */
	struct object *next; /* Pointer to the next free object*/
	size_t free; /* Positive for free objects */
} object_t;

/**
 * Structure of a single slab.
 * Slabs are arranged via a bi-directional
 * linked list.
 **/
typedef struct slab {
	struct slab *prev; /* Pointer to the previous slab */
	struct slab *next; /* Pointer to the next slab */
	struct object *head; /* Head of the free objects list */
	size_t free_objects; /* Number of free objects in a slab */
} slab_t;

/**
 * Structure of a SLAB-allocator.
 * Contains three linked lists for different
 * types of slabs among with other useful
 * information.
 **/
struct cache {
	slab_t *free; /* List of the free buffers */
	slab_t *part; /* List of the partially busy buffers */
	slab_t *busy; /* List of the busy buffers */
	size_t object_size; /* Size of allocated objects */
	int slab_order; /* Size of allocated slabs */
	size_t slab_objects; /* Number of objects within a slab */
};

/**
 * Initialization function should be called before using
 * this caching allocator for further allocations.
 * Parameters:
 *  - cache - structure to be initialized
 *  - object_size - size of objects to be
 *    allocated by this allocator
 **/
void cache_setup(struct cache *cache, size_t object_size);


/**
 * Release function should be called when an allocater is
 * no longer required. It must release the entire memory
 * occupied by the allocated.
 **/
void cache_release(struct cache *cache);


/**
 * Function to allocate memory from the caching allocater.
 * Returns a pointer to the allocated memory region of
 * size no less than object_size bytes.
 **/
void *cache_alloc(struct cache *cache);


/**
 * Function to release a previously allocated object.
 **/
void cache_free(struct cache *cache, void *ptr);


/**
 * Function releases all free slabs.
 **/
void cache_shrink(struct cache *cache);

#endif