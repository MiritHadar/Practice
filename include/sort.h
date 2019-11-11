
#ifndef OL67_SORT	
#define OL67_SORT

#include <stddef.h>     /* size_t */

typedef int (*compare_t)(const void *, const void *, void *param);
typedef size_t (*to_index_t)(const void *item, const void *args);

/*********************** Sorting functions ****************************/

void InsertionSort(void *base, size_t num_element, size_t elem_size, compare_t compare_func);

void SelectionSort(void *base, size_t num_element, size_t elem_size, compare_t compare_func);

void BubbleSort(void *base, size_t num_element, size_t elem_size, compare_t compare_func);

int CountingSort(void *base, size_t num_of_element, size_t element_size, to_index_t element_to_index, const void *args, size_t range);
				 
int RadixSort(void *base, size_t num_of_element, size_t element_size, to_index_t element_to_index, const void *args, size_t num_of_bytes);

int MergeSort(void *base, size_t num_element, size_t elem_size, compare_t compare_func);

void QuickSort(void *base, size_t num_elems, size_t elem_size, compare_t cmp_func);

void *RecursiveBinarySearch(const void *base, size_t num_of_elems, size_t elem_size, compare_t is_before, const void *key);

void *IterativeBinarySearch(const void *base, size_t num_of_elems, size_t elem_size, compare_t is_before, const void *key);

void *IterativeJumpSearch(const void *base, size_t num_of_elems, size_t elem_size, compare_t cmp_func, const void *key);

void HeapSort(void *base, size_t num_elems, size_t elem_size, compare_t cmp_func);

                
#endif	/*	OL67_SORT  */
