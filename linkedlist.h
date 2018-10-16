#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <gmp.h>
#include <cilk/cilk.h>
#include "error.h"
#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif

#define linked_list_size(list) ((list)->size)

#define linked_list_head(list) ((list)->head)
    
#define is_linked_list_empty(list) (((list)->size) == (0))

#define heap_parent(index) ((int)floorf(index/2))

#define heap_left(index) ((2*index)+1)    

#define heap_right(index) ((2*index)+2)
    
#define heap_swap(array, index, largest){\
    term_q *temp_term = array[index];\
    array[index] = array[largest];\
    array[largest] = temp_term;\
}
    
typedef enum{
    MIN_SORT = -1,
    MAX_SORT = 1
}sort_order;

/**
* Initialize and set an mpq_t type variable using <num> and <den>.
* @param mtype mpq_t type variable to be initialized
* @param num   numerator
* @param den   denominator
* @return ERROR_SUCCESS
*/
error_t create_mpq_t(mpq_t *mtype, const long int num, const long int den);

/**
 * Generate a long long unsigned int type array of a given size.
 * The array is used to represent the degree of the polynomial terms.
 * @param array_size size of the array
 * @return long long unsigned int array
 */
degrees* generate_long_long_unsigned_int_degrees(const int array_size );

/**
 * Generate a long long unsigned int type array of a given size.
 * Here the array is not empty, it is initialized by a give or specified number
 * of values. The array is used to represent the degree of the polynomial terms.
 * @param array_size size of the array
 * @param ...   user specified array values, should be array_size numbers
 * @return  long long unsigned int array
 */
degrees* generate_long_long_unsigned_int_degrees_with_values(const int array_size, ...);

/**
 * The term degree will be resized or reallocated with additional memory of size
 * (increase_by). The new degree will have old_size+increase_by size. The newly 
 * allocated memory locate is reset to 0 to remove garbage values from the memory.
 * The old value stays intact. 
 * For example if degree *deg = {3, 4, 5} after increase_by 2 will be
 *                degree *deg = {3, 4, 5, 0, 0}.
 * @param degs degrees* or array of degrees
 * @param old_size size of the degrees*
 * @param increase_by increase memory or array size by
 * @return increase array size of memory location
 */
degrees* resize_long_long_unsigned_int_degrees(degrees* degs, const int old_size, const int increase_by);

term_q *create_term_q(const mpq_t coef, degrees *degs, int num_vars);

term_q *create_term_str_q(const char *coef, const int num_vars, ...);

term_q *create_term_str_coef_q(const char* coef, degrees *degs, int num_vars);

void linked_list_init_q(linked_list_q *list);

linked_list_q *create_linked_list_q();

int linked_list_remove_q(linked_list_q *list, term_q *element);

void linked_list_destroy_q(linked_list_q *list);

void free_linked_list_term_q(term_q *term);

int linked_list_insert_q(linked_list_q *list, term_q *element,  term_q* new);

int linked_list_tail_insert_q(linked_list_q *list, term_q *element, term_q *new);

void linked_list_print_q(const linked_list_q *list, const int num_var);

void print_term_q(term_q *term, int num_var);

/**
 * The function will update the degree size of the linked list by size increase_by. This is
 * important if a newly inserted term to the list has larger degree size than the orignal list.
 * Its important to update the linked list or run the function before inserting the new 
 * node or term to the linked list.
 * Example: |<4/5>|4|5| --> |<6/7>|7|9|--> is the linked list
 *          insert |<7/9>|6|5|4|6|-->
 *          run linke list update and increase_by 2
 *          then insert the new node or term.
 * @param list
 * @param num_var
 * @param increase_by
 */
void linked_list_update_degrees_q(linked_list_q *list, int *num_var, const int increase_by);

/**
 * Compare two exponent vectors, if exponent vector a is greater than
 * exponent vector b, 1 is returned. If exponent vector b is greater than
 * exponent vector b, -1 is returned. Otherwise the two vectors are similar
 * and 0 is returned.
 * @param a vector or array of degrees
 * @param b vector or array of degrees
 * @param array_size size of the vector
 * @return 1 if a > b , -1 if a < b 1 and 0 if a == b.
 */
int compare_degrees(degrees *a, degrees *b, int array_size);

/**
 * Split the linked list in half and return a new head as a starting 
 * point for the new linked list.
 * @param list linked list
 * @return new linked list 
 */
linked_list_q *linked_list_middle_q(linked_list_q *list);

linked_list_q *linked_list_merge_sort_q(linked_list_q *list, int deg_size, sort_order order);

linked_list_q *linked_list_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order);

linked_list_q *linked_list_merge_q(linked_list_q *left, linked_list_q *right, int deg_size, sort_order order);

int is_null_list_null(int *null_list, int arr_size);

linked_list_q *linked_list_4_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_4_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_4_way_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_8_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_8_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_8_way_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_16_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_16_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_16_way_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_32_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_32_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_32_way_merge_q(linked_list_q **list, int deg_size, sort_order order);

void max_heapify(term_q **array_list, int index, int term_deg_size, int heap_size);

void min_heapify(term_q **array_list, int index, int term_deg_size, int heap_size);

void build_max_heap(term_q** array_list, int term_deg_size, int heap_size);

void build_min_heap(term_q** array_list, int term_deg_size, int heap_size);

linked_list_q *max_heap_sort(linked_list_q *list, int deg_size);

linked_list_q *min_heap_sort(linked_list_q *list, int deg_size);

linked_list_q *linked_list_4_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_4_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_4_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_8_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_8_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_8_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_16_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_16_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_16_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_32_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order);

linked_list_q *linked_list_32_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

linked_list_q *linked_list_32_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size);

/**
 * Generate a linked list with randomly generated coefficients and degree values.
 * @param size The number of list or terms to generate.
 * @param deg_size  The degree size.
 * @param bit_cnt   The bit counts of randomly generated coefficient. The length of the num/den depend on this value.
 * @return  linked list.
 */
linked_list_q *randomly_generated_linked_list_q(int size, int deg_size, int bit_cnt);

linked_list_q* generate_linked_list_from_csv_file(const char *filename);

void print_linked_list_to_file(linked_list_q *l, char** var, int numVar, char *filename, int insertVarsAtTheBeginning);

char* print_linked_list_to_string_variable(linked_list_q *list, char** var, int numVar );

char **create_dynamic_str_array(int arrSize, ...);

void free_degrees_variables(char** arr, int size);

void linked_list_deep_cpy_q(linked_list_q *src, linked_list_q *dst, int num_vars);

unsigned long int cache_size_byte();

unsigned long int appx_base_case_size_based_on_cache_mem(unsigned long int cache_size, int num_vars);



#ifdef __cplusplus
}
#endif

#endif /* LINKEDLIST_H */

