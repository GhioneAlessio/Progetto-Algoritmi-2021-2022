#include <stdlib.h>
#include <stdio.h>
#include "quicksort.h"

#define INITIAL_CAPACITY_QS	2

static unsigned long get_index_to_insert_qs (QuickSort * quick_sort, void* element);
static void insert_element_qs (QuickSort * quick_sort, void* element, unsigned long index);


QuickSort *quick_sort_create (int (*qs_precedes)(void*, void*)){
	if (precedes == NULL){
		fprintf(stderr, "quick_sort_create: precedes parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	QuickSort * quick_sort = *quick_sort = (QuickSort*) malloc (sizeof(QuickSort));
	if (quick_sort == NULL){
		fprintf(stderr, "quick_sort_create: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	quick_sort->array = (void**) malloc(INITIAL_CAPACITY_QS * sizeof(void*));
	if (quick_sort->array == NULL){
		fprintf(stderr, "quick_sort_create: unable to allocate the memory for the internal array");
		exit(EXIT_FAILURE);
	}
	quick_sort->size = 0;
	quick_sort->array_capacity = INITIAL_CAPACITY_QS;
	quick_sort->precedes = precedes;
	return quick_sort;
}

int quick_sort_is_empty(QuickSort *quick_sort){
	if (quick_sort == NULL){
		fprintf(stderr, "quick_sort_is_empty: quick_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (quick_sort->size == 0)
		return 1;
	return 0;
}

unsigned long quick_sort_size(QuickSort *quick_sort){
	if (quick_sort == NULL){
		fprintf(stderr, "quick_sort_size: quick_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	return quick_sort->size;
}

void quick_sort_add(QuickSort *quick_sort, void* element){
	if (quick_sort == NULL){
		fprintf(stderr, "quick_sort_add: quick_sort parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if (element == NULL){
		fprintf(stderr, "quick_sort_add: element parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(quick_sort->size >= quick_sort->array_capacity){
		quick_sort->array = (void**) realloc(quick_sort->array, 2*(quick_sort->array_capacity)*sizeof(void*));
		if (quick_sort->array == NULL){
			fprintf(stderr, "quick_sort_add: unable to reallocate the memory to host the new element");
			exit(EXIT_FAILURE);
		}
		quick_sort->array_capacity = 2* quick_sort->array_capacity; 
	}
	unsigned long index = get_index_to_insert_qs (quick_sort, element);
	insert_element_qs (quick_sort, element, index);
	(quick_sort->size)++;
}

void* quick_sort_get (QuickSort *quick_sort, unsigned long i){
	if (quick_sort == NULL){
		fprintf(stderr, "quick_sort_get: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	if (i >= quick_sort->size){
		fprintf(stderr, "quick_sort_get: index %lu out of bounds", i);
		exit(EXIT_FAILURE);
	}
	return (quick_sort->array)[i];
}

void* quick_sort_free_memory (QuickSort *quick_sort){
	if (quick_sort == NULL){
		fprintf(stderr, "quick_sort_free_memory: unable to allocate the memory");
		exit(EXIT_FAILURE);
	}
	free(quick_sort->array);
	free(quick_sort);
}

static unsigned long get_index_to_insert_qs (QuickSort * quick_sort, void* element){
	unsigned long i = 0;
	int cont = 1;
	while (i < quick_sort->size && cont){
		if((*(quick_sort->precedes))(element, (quick_sort->array)[i])){
			cont = 0;
		} else
			i++;
	}
	return i;
}

static void insert_element_qs (QuickSort * quick_sort, void* element, unsigned long index){
	unsigned long i;
	for (i = quick_sort->size; i > index; i--){
		(quick_sort->array)[i] = (quick_sort->array)[i - 1];
	}
	(quick_sort->array)[index] = element; 
}