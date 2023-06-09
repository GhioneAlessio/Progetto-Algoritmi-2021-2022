#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

#define INITIAL_CAPACITY_QS 2

Sort *sort_create(int (*qs_precedes)(void *, void *)){	
  if (qs_precedes == NULL){
	  fprintf(stderr, "sort_create: precedes parameter cannot be NULL");
	  exit(EXIT_FAILURE);
	}
  Sort *sort = (Sort *)malloc(sizeof(Sort));
  if (sort == NULL){
    fprintf(stderr, "sort_create: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  sort->array = (void **)malloc(INITIAL_CAPACITY_QS * sizeof(void *));
  if (sort->array == NULL){
    fprintf(stderr, "sort_create: unable to allocate the memory for the internal array");
    exit(EXIT_FAILURE);
  }
  sort->size = 0;
  sort->array_capacity = INITIAL_CAPACITY_QS;
  sort->precedes = qs_precedes;
  return sort;
}

unsigned long sort_size(Sort *sort){	
  if (sort == NULL){
    fprintf(stderr, "sort_size: sort parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return sort->size;
}

void sort_add(Sort *sort, void *element){	
  if (sort == NULL){
    fprintf(stderr, "sort_add: sort parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL){
    fprintf(stderr, "sort_add: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (sort->size >= sort->array_capacity){
    sort->array = (void **)realloc(sort->array, 2 * (sort->array_capacity) * sizeof(element));
    if (sort->array == NULL){
      fprintf(stderr, "sort_add: unable to reallocate the memory to host the new element");
      exit(EXIT_FAILURE);
    }
    sort->array_capacity = 2 * sort->array_capacity; 
  }
  (sort->array)[sort->size] = element;
  (sort->size)++;
}

void *sort_get(Sort *sort, unsigned long i){	
  if (sort == NULL){
    fprintf(stderr, "sort_get: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  if (i >= sort->size){
    fprintf(stderr, "sort_get: index %lu out of bounds", i);
    exit(EXIT_FAILURE);
	}
  return sort->array[i];
}

void *sort_free_memory(Sort *sort, void(*free_elem) (void*)){	
  if (sort == NULL){
    fprintf(stderr, "sort_free_memory: unable to allocate the memory");
    exit(EXIT_FAILURE);
  }
  if(free_elem != NULL){
    for(int i = 0; i < sort_size(sort); i++){
      free_elem(sort->array[i]);
    }
  }
  free(sort->array);
  free(sort);
}

void swap(Sort *sort, int a, int b){	
  void **tmp;
  tmp = sort->array[a];
  sort->array[a] = sort->array[b];
  sort->array[b] = tmp;
}

/*** Quicksort ***/
void quick_sort(Sort *sort, int left, int right){
  if(left < right){
    int p = partition(sort, left, right);
    quick_sort(sort, left, p);
    quick_sort(sort, p + 1, right);
  }
}

int partition(Sort *sort, int array_start, int array_end){	
  void** pivot;
  pivot = sort->array[(array_end+array_start)/2];
  swap(sort, array_start, (array_end+array_start)/2);

  int i = array_start - 1;
  int j = array_end + 1;
  while (1){
    do{
      i++;
    } while (sort->precedes(sort->array[i], pivot) == LESS_THAN);
    do{
      j--;
    } while (sort->precedes(sort->array[j], pivot) == GREATER_THAN);
    if (i >= j){
      return j;
    }
    swap(sort, i, j);
  }
}

/*** Binary Insertion Sort ***/
int binary_search(Sort *sort, void *item, int left, int right){	
  while (left <= right){
    int mid = left + (right - left) / 2;
    if ((sort->precedes(sort->array[mid], item) == EQUAL_TO))
      return mid + 1;
    else if (sort->precedes(item, sort->array[mid]) == GREATER_THAN)  
      left = mid + 1;
    else
      right = mid - 1;
  }
  return left;
}

void insertion_sort(Sort *sort, int length){	
  int i, loc, j;
  void *selected; 
  for (i = 1; i <= length; i++) {
    j = i - 1;
    selected = sort->array[i];
    loc = binary_search(sort, selected, 0, j);
    while (j >= loc) {
      sort->array[j + 1] =  sort->array[j];
      j--;
    }
    sort->array[j + 1] = selected;
  }
}