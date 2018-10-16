#include <omp.h>

#include "linkedlist.h"

static void print_k_way_merge_list(linked_list_q **list, int deg_size, int split_size);

static void print_term_q_list(term_q **array_list, int term_deg_size, int array_length);

static int list_linear_search(linked_list_q **list, int deg_size, int k_way, sort_order order);

error_t create_mpq_t(mpq_t *mtype, const long int num, const long int den){
    mpq_init(*mtype);
    mpq_set_si(*mtype, num, den);
    return ERROR_SUCCESS;
}

degrees* generate_long_long_unsigned_int_degrees(const int array_size ){
    degrees* temp_exponents = calloc(array_size, sizeof(degrees));
    if(!temp_exponents){
        printf("%s\n", "Memory not allocated.");
        return ERROR_NULL;
    }

    return temp_exponents;
}

degrees* generate_long_long_unsigned_int_degrees_with_values(const int array_size, ...){
    degrees *temp_degs = (degrees*)malloc(sizeof(degrees));
    if(!temp_degs){
        return ERROR_NULL;
    }
    va_list args;
    va_start(args, array_size);
    for(int i=0; i<array_size; i++){
        degrees temp_deg = va_arg(args, degrees);
//        if(!temp_deg){
//            return NULL;
//        }
        temp_degs[i] = temp_deg;
    }
    va_end(args);
    
    return temp_degs;
}

degrees* resize_long_long_unsigned_int_degrees(degrees* degs, const int old_size, const int increase_by){
    degs = realloc(degs, (old_size+increase_by)*sizeof(degrees));
    if(!degs){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    memset(degs+old_size, 0, increase_by*sizeof(degrees)-old_size);
    return degs;
}

term_q *create_term_q(const mpq_t coef, degrees *degs, int num_vars){
    term_q *new = (term_q*)malloc(sizeof(term_q));
    if(!new){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    mpq_init(new->coef); // huge bug if coef is not initialized
    mpq_set(new->coef, coef);
   new->deg = degs; //needs improvement
    // memcpy(&new->deg, &degs, num_vars*sizeof(degrees));
    new->next = NULL;
    return new;
}

term_q *create_term_str_coef_q(const char* coef, degrees *degs, int num_vars){
    term_q *new = (term_q*)malloc(sizeof(term_q));
    if(!new){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    
    mpq_init(new->coef);
    new->next = NULL;
    
    mpq_t temp_coef;
    mpq_init(temp_coef); // huge bug if coef is not initialized
    mpq_set_str(temp_coef, coef, 10);
    mpq_canonicalize(temp_coef);
    mpq_set(new->coef, temp_coef);
    memcpy(&new->deg, &degs, num_vars*sizeof(degrees));
    return new;
}

term_q *create_term_str_q(const char *coef, const int num_vars, ...){
    term_q *new = (term_q*)malloc(sizeof(term_q));
    if(!new){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    mpq_init(new->coef);
    new->deg = (degrees*)malloc(num_vars*sizeof(degrees));
    if(!new->deg){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    va_list args;
    va_start(args, num_vars);
    for(int i=0; i<num_vars; i++){
        degrees temp_deg = va_arg(args, degrees);
        new->deg[i] = temp_deg;
    }
    va_end(args);
    
    mpq_set_str(new->coef, coef, 10);
    mpq_canonicalize(new->coef);
    new->next = NULL;
    return new;
}

void free_linked_list_term_q(term_q *term){
    if(term != NULL){
        mpq_clear(term->coef);
        free(term->deg);
        free(term);
    }
    return;
}

void print_term_q(term_q *term, int num_var){
    if(term != NULL){
        gmp_printf("|<%Qd>|", term->coef);
        for(int i=0; i<num_var; i++){
            printf(" %lld |", term->deg[i]);
        }
        printf("\n");
    }
}

void linked_list_init_q(linked_list_q *list){
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

linked_list_q *create_linked_list_q(){
    linked_list_q *list = (linked_list_q*)malloc(sizeof(linked_list_q));
    if(!list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    linked_list_init_q(list);
    
    return list;
}

void linked_list_deep_cpy_q(linked_list_q *src, linked_list_q *dst, int num_vars){
    if(src != NULL){
        term_q *temp = src->head;
        while(temp != NULL){
            term_q *temp_dst = create_term_q(temp->coef, temp->deg, num_vars);
            linked_list_tail_insert_q(dst, NULL, temp_dst);
            temp = temp->next;
        }
    }
    return;
}

int linked_list_remove_q(linked_list_q *list, term_q *element){
    term_q *old;
    if(list->size == 0){
        return -1;
    }
    if(element == NULL){
        old = list->head;
        list->head = list->head->next;
        
        if(list->size == 1){
            list->tail == NULL;
        }
    }else{
        if(element->next == NULL){
            return -1;
        }
        old =  element->next;
        element->next = element->next->next;
        
        if(element->next == NULL){
            list->tail = element;
        }
    }
//    mpq_clear(old->coef);
//    free(old->deg);
//    free(old);
    free_linked_list_term_q(old);
    list->size--;
    return 0;
}

void linked_list_destroy_q(linked_list_q *list){
    while(list->size > 0){
        if(linked_list_remove_q(list, NULL) != 0){
            
        }
    }
    free(list);
//    memset(list, 0, sizeof(term_q));  //causes "malloc_consolidate(): invalid chunk size" error
    return;
}

int linked_list_insert_q(linked_list_q *list, term_q *element,  term_q* new){
   
    if(element == NULL){
        if(list->size == 0){
            list->tail = new;
        }
        new->next = list->head;
        list->head = new;
    }else{
        if(new->next == NULL){
            list->tail = new;
        }
        new->next = element->next;
        element->next = new;
    }
    list->size++;
    return ERROR_SUCCESS;
}

// int linked_list_tail_insert_q(linked_list_q *list, term_q *element, term_q *new){
//     if(element == NULL){
//         if(list->size == 0){
//             list->tail = new;
//             list->head = new;
//         }else{   
//             list->tail->next = new;
// //            list->tail = new;
//             list->tail = list->tail->next;
//         }
//         list->size++;
//         return ERROR_SUCCESS;
//     }    
//     return ERROR_FAILURE;
// }

inline int linked_list_tail_insert_q(linked_list_q *list, term_q *element, term_q *new){
    if(list->size == 0){
        list->tail = new;
        list->head = new;
        list->size++;
        return ERROR_SUCCESS;
    }else{   
        list->tail->next = new;
        list->tail = list->tail->next;
        list->size++;
        return ERROR_SUCCESS;
    }
    return ERROR_FAILURE;
}


void linked_list_print_q(const linked_list_q *list, const int num_var){
    term_q *temp = list->head;
    while(temp != NULL){
        gmp_printf("|<%Qd>|", temp->coef);
        for(int i=0; i<num_var; i++){
            printf(" %lld |", temp->deg[i]);
        }
        printf("-->");
        temp = temp->next;
    }
    printf("\n");
}

void linked_list_update_degrees_q(linked_list_q *list, int *num_var, const int increase_by){
    term_q *temp = list->head;
    while(temp != NULL){
        temp->deg = resize_long_long_unsigned_int_degrees(temp->deg, *num_var, (*num_var)+increase_by);
        temp = temp->next;
    }
    
    *num_var = (*num_var) + increase_by;
}

inline int compare_degrees(degrees *a, degrees *b, int array_size){
    for (int i = 0; i < array_size; ++i) {
            if (a[i] < b[i])
                return -1;
            else if (a[i] > b[i])
                return 1;
    }
    return 0;
}

linked_list_q *linked_list_middle_q(linked_list_q *list){
    term_q *temp = list->head;
    int middle = (int)floor((list->size)/2)+1;
    
    linked_list_q *ll_middle = (linked_list_q*)malloc(sizeof(linked_list_q));
    if(!ll_middle){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    linked_list_init_q(ll_middle);
    
    int i = 0;
    while(temp != NULL && i<middle){
        ll_middle->head = temp;
        temp = temp->next;
        i++;
    }
    return ll_middle;
}

linked_list_q *linked_list_merge_sort_q(linked_list_q *list, int deg_size, sort_order order){
    // if(base_case_size > 0){
    //     if(linked_list_size(list) <= base_case_size){
    //         if(order == MAX_SORT){
    //             max_heap_sort(list, deg_size);
    //         }else{
    //             min_heap_sort(list, deg_size);
    //         }
    //         return list;
    //     }
    // }else{
        if(linked_list_size(list) <= 1){
            return list;
        }
    // }
    int i = (int)floor((list->size)/2);
    int j = 0;
    linked_list_q *temp_left = create_linked_list_q();
    linked_list_q *temp_right = create_linked_list_q();
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(temp_left, NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // temp_right->head = list->head;
            // temp_right->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(temp_right, NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    temp_left = linked_list_merge_sort_q(temp_left, deg_size, order);
    temp_right = linked_list_merge_sort_q(temp_right, deg_size, order);
       
    return linked_list_merge_q(temp_left, temp_right, deg_size, order);
}

linked_list_q *linked_list_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order){
    // if(base_case_size > 0){
    //     if(linked_list_size(list) <= base_case_size){
    //         if(order == MAX_SORT){
    //             max_heap_sort(list, deg_size);
    //         }else{
    //             min_heap_sort(list, deg_size);
    //         }
    //         return list;
    //     }
    // }else{
        if(linked_list_size(list) <= 1){
            return list;
        }
    // }
    int i = (int)floor((list->size)/2);
    int j = 0;
    linked_list_q *temp_left = create_linked_list_q();
    linked_list_q *temp_right = create_linked_list_q();
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(temp_left, NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // temp_right->head = list->head;
            // temp_right->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(temp_right, NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    temp_left = cilk_spawn linked_list_merge_sort_q(temp_left, deg_size, order);
    temp_right = linked_list_merge_sort_q(temp_right, deg_size, order);
       
    return linked_list_merge_q(temp_left, temp_right, deg_size, order);
}

linked_list_q *linked_list_merge_q(linked_list_q *left, linked_list_q *right, int deg_size, sort_order order){
    linked_list_q *result = create_linked_list_q();
    
    while(!is_linked_list_empty(left) && !is_linked_list_empty(right)){ 
        if(compare_degrees(left->head->deg, right->head->deg, deg_size) == order){
            term_q *temp_term_q = left->head->next;
            linked_list_tail_insert_q(result, NULL, left->head);
            left->head = temp_term_q;
            left->size--;
        }else if(compare_degrees(left->head->deg, right->head->deg, deg_size) == 0){
            term_q *temp_term_q_left = left->head->next;
            term_q *temp_term_q_right = right->head->next;
            mpq_add(left->head->coef, left->head->coef, right->head->coef);
            if(mpq_cmp_ui(left->head->coef, 0, 1) != 0){
                linked_list_tail_insert_q(result, NULL, left->head);
                left->head = temp_term_q_left;
                free_linked_list_term_q(right->head);
                right->head = temp_term_q_right; //not freed check again
                right->size--;
                left->size--;
            }else{
                free(left->head);
                free(right->head);
                left->head = temp_term_q_left;
                right->head = temp_term_q_right; //not freed check again
                right->size--;
                left->size--;
            }
        }else{
                term_q *temp_term_q = right->head->next;
                linked_list_tail_insert_q(result, NULL, right->head);
                right->head = temp_term_q;
                right->size--;
        }
    }
    while(!is_linked_list_empty(left)){
        term_q *temp_term_q = left->head->next;
        linked_list_tail_insert_q(result, NULL, left->head);
        left->head = temp_term_q;
        left->size--;
    }
    while(!is_linked_list_empty(right)){
        term_q *temp_term_q = right->head->next;
        linked_list_tail_insert_q(result, NULL, right->head);
        right->head = temp_term_q;
        right->size--;
    }

    linked_list_destroy_q(left);
    linked_list_destroy_q(right);        

    return result;
}

static void print_term_q_list(term_q **array_list, int term_deg_size, int array_length){
    for(int i =0; i<array_length; i++){
        print_term_q(array_list[i], term_deg_size);
    }
}

inline void max_heapify(term_q **array_list, int index, int term_deg_size, int heap_size){
    int left = heap_left(index);
    int right = heap_right(index);
    int largest = -1; //initialized, largest index not known yet
    
    if(left < heap_size && (compare_degrees(array_list[left]->deg, array_list[index]->deg, term_deg_size) == 1)){
        largest = left;
    }else{
        largest = index;
    }
    if(right < heap_size && (compare_degrees(array_list[right]->deg, array_list[largest]->deg, term_deg_size) == 1)){
        largest = right;
    }
    if(largest != index){
        heap_swap(array_list, index, largest);
        max_heapify(array_list, largest, term_deg_size, heap_size);
    }
}

inline void min_heapify(term_q **array_list, int index, int term_deg_size, int heap_size){
    int left = heap_left(index);
    int right = heap_right(index);
    int largest = -1; //initialized, largest index not known yet
    
    if(left < heap_size && (compare_degrees(array_list[left]->deg, array_list[index]->deg, term_deg_size) == -1)){
        largest = left;
    }else{
        largest = index;
    }
    if(right < heap_size && (compare_degrees(array_list[right]->deg, array_list[largest]->deg, term_deg_size) == -1)){
        largest = right;
    }
    if(largest != index){
        heap_swap(array_list, index, largest);
        min_heapify(array_list, largest, term_deg_size, heap_size);
    }
}

void build_max_heap(term_q **array_list, int term_deg_size, int heap_size){
    int i = (int)floor(heap_size/2)-1;
    // printf("i : %d\n", i);
    for(; i>=0; i--){
        max_heapify(array_list, i, term_deg_size, heap_size);
    }
}

void build_min_heap(term_q **array_list, int term_deg_size, int heap_size){
    int i = (int)floor(heap_size/2)-1;
    for(; i>=0; i--){
        min_heapify(array_list, i, term_deg_size, heap_size);
    }
}
//can be changed into a void function.
linked_list_q *max_heap_sort(linked_list_q *list, int deg_size){
    int list_size = list->size;
    int heap_size = list->size;
    
    term_q **temp_list = malloc(heap_size*sizeof(term_q*));
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<list_size; i++){
        temp_list[i] = list->head;
        list->head = list->head->next;
        list->size--;
        temp_list[i]->next = NULL;
    }
    
    // build_max_heap(temp_list, deg_size, list_size);
    int i = (int)floor(heap_size/2)-1;
    for(; i>=0; i--){
        max_heapify(temp_list, i, deg_size, heap_size);
    }
    
    for(int i=list_size-1; i>=0; i--){
        linked_list_tail_insert_q(list, NULL, temp_list[0]);
        heap_swap(temp_list, 0, i);
        max_heapify(temp_list, 0, deg_size, i);
    }
    free(temp_list);
    return list;
}
//can be changed into a void function
linked_list_q *min_heap_sort(linked_list_q *list, int deg_size){
    int list_size = list->size;
    int heap_size = list->size;
    
    term_q **temp_list = malloc(heap_size*sizeof(term_q*));
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<list_size; i++){
        temp_list[i] = list->head;
        list->head = list->head->next;
        list->size--;
        temp_list[i]->next = NULL;
    }
    
    // build_min_heap(temp_list, deg_size, list_size);
    int i = (int)floor(heap_size/2)-1;
    for(; i>=0; i--){
        min_heapify(temp_list, i, deg_size, heap_size);
    }
    
    for(int i=list_size-1; i>=0; i--){
        linked_list_tail_insert_q(list, NULL, temp_list[0]);
        heap_swap(temp_list, 0, i);
        min_heapify(temp_list, 0, deg_size, i);
    }
    free(temp_list);
    return list;
}

int is_null_list_null(int *null_list, int arr_size){
    int num_null_list = 0;
    for(int i=0; i<arr_size; i++){
        if(null_list[i] == 0){
            num_null_list++;
        }
    }
    if(num_null_list >= (arr_size-1)){
        return 1;
    }else{
        return 0;
    }
}

static int list_linear_search(linked_list_q **list, int deg_size, int k_way, sort_order order){
    int largest_index = -1;
    for(int k=0; k<k_way; k++){
        if(!is_linked_list_empty(list[k]) && largest_index == -1){
            largest_index = k;
//            printf("if: largest_index = %d <-> k = %d\n", largest_index, k);
        }else if(!is_linked_list_empty(list[k]) && (compare_degrees(list[k]->head->deg, list[largest_index]->head->deg, deg_size) == order)){
            largest_index = k;
//            printf("2 else if: largest_index = %d <-> k = %d\n", largest_index, k);
        }
    }
    return largest_index;
}

static void print_k_way_merge_list(linked_list_q **list, int deg_size, int split_size){
    for(int i=0; i<split_size; i++){
        printf("[+++] list: %d - size: %d --  ", i, linked_list_size(list[i]));
        linked_list_print_q(list[i], deg_size);
    }
    return;
}

linked_list_q *linked_list_4_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 4;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){// note: it might faster to write the insert code than call linked_list_insert_q.
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        // }else if(j < (i*4)){
        }else{
            // l[3]->head = list->head;
            // l[3]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[3], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        // }else{
        //     break;
        // }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);
    
    l[0] = linked_list_4_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_4_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_4_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_4_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    
    return linked_list_4_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_4_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 4;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[3]->head = list->head;
            // l[3]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[3], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);
    
    l[0] = cilk_spawn linked_list_4_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_4_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_4_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_4_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    cilk_sync;
    
    return linked_list_4_way_merge_q(l, deg_size, order);
}



linked_list_q *linked_list_4_way_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 4;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL;    //Tracks the previous term , the term before largest->tail.
    
    int null_list[kway];       //used to keep track of the null list in the array
    for(int k=0; k<kway; k++){
        null_list[k] = 1;
    }
    
    while(!is_null_list_null(null_list, kway)){
        
        int largest_index = list_linear_search(list, deg_size, kway, order);        
        
        int cmp = order;
        term_q *temp_term_q = list[largest_index]->head->next;
        largest = list[largest_index]->head;
        list[largest_index]->size--;
        largest->next = NULL;
        if(result->tail != NULL){
            /*Compare the current term with the next term*/
            cmp = compare_degrees(result->tail->deg, largest->deg, deg_size);
        }
        /*The current term and the next term are similar, add the coef and check*/
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, largest->coef);
            /*If the coefficient after addition is zero, the term need to be
             removed from the list. The following condition null the previous
             term. Need improvement, mpz_t coef is not  properly released, 
             degrees* deg is not properly released term_q* is not properly released.*/
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
//                result->tail->next = NULL; //comment out, segmentation fault for MIN_SORT
                result->size--;
            }
        }else if(cmp == order){
            previous = result->tail; //previous variable is updated every time a new term is inserted
            linked_list_tail_insert_q(result, NULL, largest);
            list[largest_index]->head = temp_term_q;
        }
        
        largest = NULL;
        largest_index = -1;
        
        for(int k=0; k<kway; k++){
            if(is_linked_list_empty(list[k])){
                null_list[k] = 0;
//                printf("if null : largest_index = %d <-> k = %d\n", largest_index, k);
            }
        }
    } 
    
    for(int k=0; k<kway; k++){
        if(!is_linked_list_empty(list[k])){
            while(!is_linked_list_empty(list[k])){
                term_q *temp_term_q = list[k]->head->next;
                linked_list_tail_insert_q(result, NULL, list[k]->head);
                list[k]->head->next = NULL;
                list[k]->size--;
                list[k]->head = temp_term_q;
            }
        }
    }
    for(int i = 0; i<kway; i++){//added oct 3
        linked_list_destroy_q(list[i]);
    }
    free(list);
    
    return result;
}

linked_list_q *linked_list_8_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 8;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[7]->head = list->head;
            // l[7]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[7], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_8_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_8_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_8_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_8_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = linked_list_8_way_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = linked_list_8_way_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = linked_list_8_way_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_8_way_merge_sort_q(l[7], deg_size, order, base_case_size);
        
    return linked_list_8_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_8_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 8;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[7]->head = list->head;
            // l[7]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[7], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_8_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_8_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_8_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = cilk_spawn linked_list_8_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = cilk_spawn linked_list_8_way_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = cilk_spawn linked_list_8_way_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = cilk_spawn linked_list_8_way_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_8_way_merge_sort_q(l[7], deg_size, order, base_case_size);
        
    return linked_list_8_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_8_way_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 8;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL;
    
    int null_list[kway];       //used to keep track of the null list in the array
    for(int k=0; k<kway; k++){
        null_list[k] = 1;
    }
    
    while(!is_null_list_null(null_list, kway)){
        
        int largest_index = list_linear_search(list, deg_size, kway, order);
        
        int cmp = order;
        term_q *temp_term_q = list[largest_index]->head->next;
        largest = list[largest_index]->head;
        list[largest_index]->size--;
        largest->next = NULL;
        
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, largest->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, largest->coef);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
//                result->tail->next = NULL;
                result->size--;
            }
        }else if(cmp == order){
            previous = result->tail;
            linked_list_tail_insert_q(result, NULL, largest);
            list[largest_index]->head = temp_term_q;
        }
        
        largest = NULL;
        largest_index = -1;
//        printf("RESULT: ");
//        linked_list_print_q(result, deg_size);
        
        for(int k=0; k<kway; k++){
            if(is_linked_list_empty(list[k])){
                null_list[k] = 0;
//                printf("if null : largest_index = %d <-> k = %d\n", largest_index, k);
            }
        }
    } 
    
    for(int k=0; k<kway; k++){
        if(!is_linked_list_empty(list[k])){
            while(!is_linked_list_empty(list[k])){\
                term_q *temp_term_q = list[k]->head->next;
                linked_list_tail_insert_q(result, NULL, list[k]->head);
                list[k]->head->next = NULL;
                list[k]->size--;
                list[k]->head = temp_term_q;
            }
        }
    }

    for(int i = 0; i<kway; i++){//added oct 3
        linked_list_destroy_q(list[i]);
    }
    free(list);
    
    return result;
}

linked_list_q *linked_list_16_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 16;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[15]->head = list->head;
            // l[15]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[15], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_16_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_16_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_16_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_16_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = linked_list_16_way_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = linked_list_16_way_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = linked_list_16_way_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_16_way_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = linked_list_16_way_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = linked_list_16_way_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = linked_list_16_way_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = linked_list_16_way_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = linked_list_16_way_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = linked_list_16_way_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = linked_list_16_way_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = linked_list_16_way_merge_sort_q(l[15], deg_size, order, base_case_size);
    
    return linked_list_16_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_16_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 16;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[15]->head = list->head;
            // l[15]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[15], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_16_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_16_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_16_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = cilk_spawn linked_list_16_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = cilk_spawn linked_list_16_way_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = cilk_spawn linked_list_16_way_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = cilk_spawn linked_list_16_way_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = cilk_spawn linked_list_16_way_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = cilk_spawn linked_list_16_way_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = cilk_spawn linked_list_16_way_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = cilk_spawn linked_list_16_way_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = cilk_spawn linked_list_16_way_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = cilk_spawn linked_list_16_way_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = cilk_spawn linked_list_16_way_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = cilk_spawn linked_list_16_way_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = linked_list_16_way_merge_sort_q(l[15], deg_size, order, base_case_size);
    
    return linked_list_16_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_16_way_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 16;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL;
    
    int null_list[kway];       //used to keep track of the null list in the array
    for(int k=0; k<kway; k++){
        null_list[k] = 1;
    }
    
    while(!is_null_list_null(null_list, kway)){
        
        int largest_index = list_linear_search(list, deg_size, kway, order);
        
        int cmp = order;
        term_q *temp_term_q = list[largest_index]->head->next;
        largest = list[largest_index]->head;
        list[largest_index]->size--;
        largest->next = NULL;
        
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, largest->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, largest->coef);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
//                result->tail->next = NULL;
                result->size--;
            }
        }else if(cmp == order){
            previous = result->tail;
            linked_list_tail_insert_q(result, NULL, largest);
            list[largest_index]->head = temp_term_q;
        }
        
        largest = NULL;
        largest_index = -1;
//        printf("RESULT: ");
//        linked_list_print_q(result, deg_size);
        
        for(int k=0; k<kway; k++){
            if(is_linked_list_empty(list[k])){
                null_list[k] = 0;
//                printf("if null : largest_index = %d <-> k = %d\n", largest_index, k);
            }
        }
    } 
    
    for(int k=0; k<kway; k++){
        if(!is_linked_list_empty(list[k])){
            while(!is_linked_list_empty(list[k])){\
                term_q *temp_term_q = list[k]->head->next;
                linked_list_tail_insert_q(result, NULL, list[k]->head);
                list[k]->head->next = NULL;
                list[k]->size--;
                list[k]->head = temp_term_q;
            }
        }
    }

    for(int i = 0; i<kway; i++){//added oct 3
        linked_list_destroy_q(list[i]);
    }
    free(list);
    
    return result;
}

linked_list_q *linked_list_32_way_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 32;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*16)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[15], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*17)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[16], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*18)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[17], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*19)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[18], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*20)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[19], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*21)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[20], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*22)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[21], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*23)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[22], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*24)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[23], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*25)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[24], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*26)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[25], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*27)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[26], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*28)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[27], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*29)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[28], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*30)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[29], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*31)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[30], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[31]->head = list->head;
            // l[31]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[31], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_32_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_32_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_32_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_32_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = linked_list_32_way_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = linked_list_32_way_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = linked_list_32_way_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_32_way_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = linked_list_32_way_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = linked_list_32_way_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = linked_list_32_way_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = linked_list_32_way_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = linked_list_32_way_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = linked_list_32_way_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = linked_list_32_way_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = linked_list_32_way_merge_sort_q(l[15], deg_size, order, base_case_size);
    l[16] = linked_list_32_way_merge_sort_q(l[16], deg_size, order, base_case_size);
    l[17] = linked_list_32_way_merge_sort_q(l[17], deg_size, order, base_case_size);
    l[18] = linked_list_32_way_merge_sort_q(l[18], deg_size, order, base_case_size);
    l[19] = linked_list_32_way_merge_sort_q(l[19], deg_size, order, base_case_size);
    l[20] = linked_list_32_way_merge_sort_q(l[20], deg_size, order, base_case_size);
    l[21] = linked_list_32_way_merge_sort_q(l[21], deg_size, order, base_case_size);
    l[22] = linked_list_32_way_merge_sort_q(l[22], deg_size, order, base_case_size);
    l[23] = linked_list_32_way_merge_sort_q(l[23], deg_size, order, base_case_size);
    l[24] = linked_list_32_way_merge_sort_q(l[24], deg_size, order, base_case_size);
    l[25] = linked_list_32_way_merge_sort_q(l[25], deg_size, order, base_case_size);
    l[26] = linked_list_32_way_merge_sort_q(l[26], deg_size, order, base_case_size);
    l[27] = linked_list_32_way_merge_sort_q(l[27], deg_size, order, base_case_size);
    l[28] = linked_list_32_way_merge_sort_q(l[28], deg_size, order, base_case_size);
    l[29] = linked_list_32_way_merge_sort_q(l[29], deg_size, order, base_case_size);
    l[30] = linked_list_32_way_merge_sort_q(l[30], deg_size, order, base_case_size);
    l[31] = linked_list_32_way_merge_sort_q(l[31], deg_size, order, base_case_size);
        
    return linked_list_32_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_32_way_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 32;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            list = linked_list_merge_sort_q(list, deg_size, order);
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*16)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[15], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*17)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[16], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*18)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[17], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*19)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[18], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*20)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[19], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*21)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[20], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*22)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[21], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*23)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[22], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*24)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[23], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*25)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[24], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*26)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[25], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*27)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[26], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*28)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[27], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*29)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[28], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*30)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[29], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*31)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[30], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[31]->head = list->head;
            // l[31]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[31], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_32_way_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_32_way_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_32_way_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = cilk_spawn linked_list_32_way_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = cilk_spawn linked_list_32_way_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = cilk_spawn linked_list_32_way_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = cilk_spawn linked_list_32_way_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = cilk_spawn linked_list_32_way_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = cilk_spawn linked_list_32_way_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = cilk_spawn linked_list_32_way_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = cilk_spawn linked_list_32_way_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = cilk_spawn linked_list_32_way_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = cilk_spawn linked_list_32_way_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = cilk_spawn linked_list_32_way_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = cilk_spawn linked_list_32_way_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = cilk_spawn linked_list_32_way_merge_sort_q(l[15], deg_size, order, base_case_size);
    l[16] = cilk_spawn linked_list_32_way_merge_sort_q(l[16], deg_size, order, base_case_size);
    l[17] = cilk_spawn linked_list_32_way_merge_sort_q(l[17], deg_size, order, base_case_size);
    l[18] = cilk_spawn linked_list_32_way_merge_sort_q(l[18], deg_size, order, base_case_size);
    l[19] = cilk_spawn linked_list_32_way_merge_sort_q(l[19], deg_size, order, base_case_size);
    l[20] = cilk_spawn linked_list_32_way_merge_sort_q(l[20], deg_size, order, base_case_size);
    l[21] = cilk_spawn linked_list_32_way_merge_sort_q(l[21], deg_size, order, base_case_size);
    l[22] = cilk_spawn linked_list_32_way_merge_sort_q(l[22], deg_size, order, base_case_size);
    l[23] = cilk_spawn linked_list_32_way_merge_sort_q(l[23], deg_size, order, base_case_size);
    l[24] = cilk_spawn linked_list_32_way_merge_sort_q(l[24], deg_size, order, base_case_size);
    l[25] = cilk_spawn linked_list_32_way_merge_sort_q(l[25], deg_size, order, base_case_size);
    l[26] = cilk_spawn linked_list_32_way_merge_sort_q(l[26], deg_size, order, base_case_size);
    l[27] = cilk_spawn linked_list_32_way_merge_sort_q(l[27], deg_size, order, base_case_size);
    l[28] = cilk_spawn linked_list_32_way_merge_sort_q(l[28], deg_size, order, base_case_size);
    l[29] = cilk_spawn linked_list_32_way_merge_sort_q(l[29], deg_size, order, base_case_size);
    l[30] = cilk_spawn linked_list_32_way_merge_sort_q(l[30], deg_size, order, base_case_size);
    l[31] = linked_list_32_way_merge_sort_q(l[31], deg_size, order, base_case_size);
    cilk_sync;    
    
    return linked_list_32_way_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_32_way_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 32;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL;
    
    int null_list[kway];       //used to keep track of the null list in the array
    for(int k=0; k<kway; k++){
        null_list[k] = 1;
    }
    
    while(!is_null_list_null(null_list, kway)){
        
        int largest_index = list_linear_search(list, deg_size, kway, order);
        
        int cmp = order;
        term_q *temp_term_q = list[largest_index]->head->next;
        largest = list[largest_index]->head;
        list[largest_index]->size--;
        largest->next = NULL;
        
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, largest->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, largest->coef);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
//                result->tail->next = NULL;
                result->size--;
            }
        }else if(cmp == order){
            previous = result->tail;
            linked_list_tail_insert_q(result, NULL, largest);
            list[largest_index]->head = temp_term_q;
        }
//        print_term_q(largest, deg_size);
        largest = NULL;
        largest_index = -1;
//        printf("RESULT: ");
//        linked_list_print_q(result, deg_size);
        
        for(int k=0; k<kway; k++){
            if(is_linked_list_empty(list[k])){
                null_list[k] = 0;
//                printf("if null : largest_index = %d <-> k = %d\n", largest_index, k);
            }
        }
    } 
    
    for(int k=0; k<kway; k++){
        if(!is_linked_list_empty(list[k])){
            while(!is_linked_list_empty(list[k])){\
                term_q *temp_term_q = list[k]->head->next;
                linked_list_tail_insert_q(result, NULL, list[k]->head);
                list[k]->head->next = NULL;
                list[k]->size--;
                list[k]->head = temp_term_q;
            }
        }
    }
    
    for(int i = 0; i<kway; i++){//added oct 3
        linked_list_destroy_q(list[i]);
    }
    free(list);

    return result;
}

linked_list_q *linked_list_4_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 4;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[3]->head = list->head;
            // l[3]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[3], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_4_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_4_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_4_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_4_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    
    return linked_list_4_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_4_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 4;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[3]->head = list->head;
            // l[3]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[3], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0; 
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_4_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);        
    l[1] = cilk_spawn linked_list_4_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);        
    l[2] = cilk_spawn linked_list_4_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);       
    l[3] = linked_list_4_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    
    return linked_list_4_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_4_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 4;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL; //Tracks the previous term , the term before largest->tail.
    
    int null_list[kway];       //used to keep track of the null list in the array
    int heap_size = kway;
        
    term_q **temp_list = malloc(kway*sizeof(term_q*));
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    
    for(int i =0, array_index=0; i<kway; i++){
        if(list[i]->head != NULL){
            null_list[array_index] = 1;
            temp_list[array_index] = list[i]->head;
            array_index++;
        }
    }
    
    while(heap_size != 0){
        int cmp = order;
        if(order == MAX_SORT){
            build_max_heap(temp_list, deg_size, heap_size);
        }else{
            build_min_heap(temp_list, deg_size, heap_size);
        }
        /*Before inserting the term to the final linked list, check if the previous
         * have the same degree. If they have the same degree <cmp> is 0. In this
         * case add the coefficient to the previous term and free the current term
         * to be added i.e(term_temp[0]). This is done if <cmp == 0>.
        */
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, temp_list[0]->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, temp_list[0]->coef);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
                result->size--;
                temp_list[0] = temp_list[0]->next; //if the addition result in a zero coefficient needs to update the top of array list
            }
        }else if(cmp == order){
            previous = result->tail; //previous variable is updated every time a new term is inserted
            if(mpq_cmp_si(temp_list[0]->coef, 0, 1) != 0){
                linked_list_tail_insert_q(result, NULL, temp_list[0]);
            }
            temp_list[0] = temp_list[0]->next;
        }
        if(temp_list[0]==NULL){
            temp_list[0] = temp_list[heap_size-1];
            heap_size--;
        }
    }
    return result;
}

linked_list_q *linked_list_8_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 8;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[7]->head = list->head;
            // l[7]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[7], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_8_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_8_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_8_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_8_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = linked_list_8_way_heap_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = linked_list_8_way_heap_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = linked_list_8_way_heap_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_8_way_heap_merge_sort_q(l[7], deg_size, order, base_case_size);
    
    return linked_list_8_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_8_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 8;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[7]->head = list->head;
            // l[7]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[7], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = cilk_spawn linked_list_8_way_heap_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_8_way_heap_merge_sort_q(l[7], deg_size, order, base_case_size);
    cilk_sync;

    return linked_list_8_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_8_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 8;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL; //Tracks the previous term , the term before largest->tail.
    
    int null_list[kway];       //used to keep track of the null list in the array
    int heap_size = kway;
    
    term_q **temp_list = malloc(kway*sizeof(term_q*));
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    
    for(int i =0, array_index=0; i<kway; i++){
        if(list[i]->head != NULL){
            null_list[array_index] = 1;
            temp_list[array_index] = list[i]->head;
            array_index++;
        }
    }
    
    while(heap_size != 0){
        int cmp = order;
        if(order == MAX_SORT){
            build_max_heap(temp_list, deg_size, heap_size);
        }else{
            build_min_heap(temp_list, deg_size, heap_size);
        }
        /*Before inserting the term to the final linked list, check if the previous
         * have the same degree. If they have the same degree <cmp> is 0. In this
         * case add the coefficient to the previous term and free the current term
         * to be added i.e(term_temp[0]). This is done if <cmp == 0>.
        */
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, temp_list[0]->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, temp_list[0]->coef);
            // printf("YES 0 \n");
            // print_term_q(temp_list[0], deg_size);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
                // if(order == MAX_SORT)//SHOULD BE TEMPORARY
                //     result->tail->next = NULL;
                result->size--;
                temp_list[0] = temp_list[0]->next; //if the addition result in a zero coefficient needs to update the top of array list
            }
            // else{
            //     term_q *temp = temp_list[0];
            //     temp_list[0] = temp_list[0]->next;
            //     free_linked_list_term_q(temp);
            // }
        }else if(cmp == order){
            previous = result->tail; //previous variable is updated every time a new term is inserted
            if(mpq_cmp_si(temp_list[0]->coef, 0, 1) != 0){//SHOULD BE TEMPORARY
                linked_list_tail_insert_q(result, NULL, temp_list[0]);
            }
            temp_list[0] = temp_list[0]->next;
        }
        if(temp_list[0]==NULL){
            temp_list[0] = temp_list[heap_size-1];
            heap_size--;
        }
        // if(order == MAX_SORT){
        //     build_max_heap(temp_list, deg_size, heap_size);
        // }else{
        //     build_min_heap(temp_list, deg_size, heap_size);
        // }
    }
    
//    linked_list_print_q(result, deg_size);
    return result;
}

linked_list_q *linked_list_16_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 16;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[15]->head = list->head;
            // l[15]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[15], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_16_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_16_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_16_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_16_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = linked_list_16_way_heap_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = linked_list_16_way_heap_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = linked_list_16_way_heap_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_16_way_heap_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = linked_list_16_way_heap_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = linked_list_16_way_heap_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = linked_list_16_way_heap_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = linked_list_16_way_heap_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = linked_list_16_way_heap_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = linked_list_16_way_heap_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = linked_list_16_way_heap_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = linked_list_16_way_heap_merge_sort_q(l[15], deg_size, order, base_case_size);
    
    return linked_list_16_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_16_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 16;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[15]->head = list->head;
            // l[15]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[15], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = cilk_spawn linked_list_16_way_heap_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = linked_list_16_way_heap_merge_sort_q(l[15], deg_size, order, base_case_size);
    cilk_sync; 

    return linked_list_16_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_16_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 16;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL; //Tracks the previous term , the term before largest->tail.
    
    int null_list[kway];       //used to keep track of the null list in the array
    int heap_size = kway;
    
    term_q **temp_list = malloc(kway*sizeof(term_q*));
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    
    for(int i =0, array_index=0; i<kway; i++){
        
        if(list[i]->head != NULL){
            null_list[array_index] = 1;
            temp_list[array_index] = list[i]->head;
            array_index++;
        }
    }
    
    while(heap_size != 0){
        int cmp = order;
        if(order == MAX_SORT){
            build_max_heap(temp_list, deg_size, heap_size);
        }else{
            build_min_heap(temp_list, deg_size, heap_size);
        }
        /*Before inserting the term to the final linked list, check if the previous
         * have the same degree. If they have the same degree <cmp> is 0. In this
         * case add the coefficient to the previous term and free the current term
         * to be added i.e(term_temp[0]). This is done if <cmp == 0>.
        */
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, temp_list[0]->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, temp_list[0]->coef);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
                // if(order == MAX_SORT) //TEMPORARY CHANGE TO REMOVE 0 COEF FROM THE LIST
                //     result->tail->next = NULL;
                result->size--;
                temp_list[0] = temp_list[0]->next; //if the addition result in a zero coefficient needs to update the top of array list
            }
            // else{
            //     term_q *temp = temp_list[0];
            //     temp_list[0] = temp_list[0]->next;
            //     free_linked_list_term_q(temp);
            // }
        }else if(cmp == order){
            previous = result->tail; //previous variable is updated every time a new term is inserted
            if(mpq_cmp_si(temp_list[0]->coef, 0, 1) != 0){ //TEMPORARY
                linked_list_tail_insert_q(result, NULL, temp_list[0]);
            }
            temp_list[0] = temp_list[0]->next;
        }
        if(temp_list[0]==NULL){
            temp_list[0] = temp_list[heap_size-1];
            heap_size--;
        }
        // if(order == MAX_SORT){
        //     build_max_heap(temp_list, deg_size, heap_size);
        // }else{
        //     build_min_heap(temp_list, deg_size, heap_size);
        // }
    }
    
    return result;
}

linked_list_q *linked_list_32_way_heap_merge_sort_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 32;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*16)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[15], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*17)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[16], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*18)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[17], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*19)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[18], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*20)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[19], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*21)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[20], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*22)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[21], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*23)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[22], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*24)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[23], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*25)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[24], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*26)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[25], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*27)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[26], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*28)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[27], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*29)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[28], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*30)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[29], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*31)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[30], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[31]->head = list->head;
            // l[31]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[31], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = linked_list_32_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = linked_list_32_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = linked_list_32_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = linked_list_32_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = linked_list_32_way_heap_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = linked_list_32_way_heap_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = linked_list_32_way_heap_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = linked_list_32_way_heap_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = linked_list_32_way_heap_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = linked_list_32_way_heap_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = linked_list_32_way_heap_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = linked_list_32_way_heap_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = linked_list_32_way_heap_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = linked_list_32_way_heap_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = linked_list_32_way_heap_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = linked_list_32_way_heap_merge_sort_q(l[15], deg_size, order, base_case_size);
    l[16] = linked_list_32_way_heap_merge_sort_q(l[16], deg_size, order, base_case_size);
    l[17] = linked_list_32_way_heap_merge_sort_q(l[17], deg_size, order, base_case_size);
    l[18] = linked_list_32_way_heap_merge_sort_q(l[18], deg_size, order, base_case_size);
    l[19] = linked_list_32_way_heap_merge_sort_q(l[19], deg_size, order, base_case_size);
    l[20] = linked_list_32_way_heap_merge_sort_q(l[20], deg_size, order, base_case_size);
    l[21] = linked_list_32_way_heap_merge_sort_q(l[21], deg_size, order, base_case_size);
    l[22] = linked_list_32_way_heap_merge_sort_q(l[22], deg_size, order, base_case_size);
    l[23] = linked_list_32_way_heap_merge_sort_q(l[23], deg_size, order, base_case_size);
    l[24] = linked_list_32_way_heap_merge_sort_q(l[24], deg_size, order, base_case_size);
    l[25] = linked_list_32_way_heap_merge_sort_q(l[25], deg_size, order, base_case_size);
    l[26] = linked_list_32_way_heap_merge_sort_q(l[26], deg_size, order, base_case_size);
    l[27] = linked_list_32_way_heap_merge_sort_q(l[27], deg_size, order, base_case_size);
    l[28] = linked_list_32_way_heap_merge_sort_q(l[28], deg_size, order, base_case_size);
    l[29] = linked_list_32_way_heap_merge_sort_q(l[29], deg_size, order, base_case_size);
    l[30] = linked_list_32_way_heap_merge_sort_q(l[30], deg_size, order, base_case_size);
    l[31] = linked_list_32_way_heap_merge_sort_q(l[31], deg_size, order, base_case_size);
    
    return linked_list_32_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_32_way_heap_merge_sort_parallel_q(linked_list_q *list, int deg_size, sort_order order, long int base_case_size){
    const int kway = 32;
    if(base_case_size > 0){
        if(linked_list_size(list) <= base_case_size){
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }else{
        if(linked_list_size(list) <= kway){
            // list = linked_list_merge_sort_q(list, deg_size, order);
            if(order == MAX_SORT){
                max_heap_sort(list, deg_size);
            }else{
                min_heap_sort(list, deg_size);
            }
            return list;
        }
    }
    int i = (int)floor((list->size)/kway);
    
    int j = 0;
    linked_list_q **l = malloc(kway*sizeof(linked_list_q*));
    if(!l){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    for(int i =0; i<kway; i++){
        l[i] = create_linked_list_q();
    }
    
    while(list->head != NULL){
        if(j < i){
            term_q *temp_term_q = list->head->next;
            list->head->next = NULL;
            linked_list_insert_q(l[0], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*2)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[1], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*3)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[2], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*4)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[3], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*5)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[4], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*6)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[5], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*7)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[6], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*8)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[7], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*9)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[8], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*10)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[9], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*11)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[10], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*12)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[11], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*13)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[12], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*14)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[13], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*15)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[14], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*16)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[15], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*17)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[16], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*18)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[17], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*19)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[18], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*20)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[19], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*21)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[20], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*22)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[21], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*23)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[22], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*24)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[23], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*25)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[24], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*26)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[25], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*27)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[26], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*28)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[27], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*29)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[28], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*30)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[29], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else if(j < (i*31)){
            term_q *temp_term_q = list->head->next;
            linked_list_insert_q(l[30], NULL, list->head);
            list->head = temp_term_q;
            list->size--;
        }else{
            // l[31]->head = list->head;
            // l[31]->size = list->size;
            while(list->size > 0){
                term_q *temp_term_q = list->head->next;
                linked_list_insert_q(l[31], NULL, list->head);
                list->head = temp_term_q;
                list->size--;
            }
            break;
        }
        j++;
    }
    
    // list->size = 0;
    // list = NULL;
    linked_list_destroy_q(list);

    l[0] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[0], deg_size, order, base_case_size);
    l[1] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[1], deg_size, order, base_case_size);
    l[2] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[2], deg_size, order, base_case_size);
    l[3] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[3], deg_size, order, base_case_size);
    l[4] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[4], deg_size, order, base_case_size);
    l[5] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[5], deg_size, order, base_case_size);
    l[6] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[6], deg_size, order, base_case_size);
    l[7] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[7], deg_size, order, base_case_size);
    l[8] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[8], deg_size, order, base_case_size);
    l[9] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[9], deg_size, order, base_case_size);
    l[10] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[10], deg_size, order, base_case_size);
    l[11] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[11], deg_size, order, base_case_size);
    l[12] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[12], deg_size, order, base_case_size);
    l[13] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[13], deg_size, order, base_case_size);
    l[14] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[14], deg_size, order, base_case_size);
    l[15] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[15], deg_size, order, base_case_size);
    l[16] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[16], deg_size, order, base_case_size);
    l[17] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[17], deg_size, order, base_case_size);
    l[18] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[18], deg_size, order, base_case_size);
    l[19] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[19], deg_size, order, base_case_size);
    l[20] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[20], deg_size, order, base_case_size);
    l[21] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[21], deg_size, order, base_case_size);
    l[22] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[22], deg_size, order, base_case_size);
    l[23] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[23], deg_size, order, base_case_size);
    l[24] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[24], deg_size, order, base_case_size);
    l[25] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[25], deg_size, order, base_case_size);
    l[26] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[26], deg_size, order, base_case_size);
    l[27] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[27], deg_size, order, base_case_size);
    l[28] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[28], deg_size, order, base_case_size);
    l[29] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[29], deg_size, order, base_case_size);
    l[30] = cilk_spawn linked_list_32_way_heap_merge_sort_q(l[30], deg_size, order, base_case_size);
    l[31] = linked_list_32_way_heap_merge_sort_q(l[31], deg_size, order, base_case_size);
    cilk_sync;
    
    return linked_list_32_way_heap_merge_q(l, deg_size, order);
}

linked_list_q *linked_list_32_way_heap_merge_q(linked_list_q **list, int deg_size, sort_order order){
    const int kway = 32;
    linked_list_q *result = create_linked_list_q();
    term_q *largest = NULL;
    term_q *previous = NULL; //Tracks the previous term , the term before largest->tail.
    
    int null_list[kway];       //used to keep track of the null list in the array
    int heap_size = kway;
       
    term_q **temp_list = malloc(kway*sizeof(term_q*));
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    
    for(int i =0, array_index=0; i<kway; i++){
        
        if(list[i]->head != NULL){
            null_list[array_index] = 1;
            temp_list[array_index] = list[i]->head;
            array_index++;
        }
    }
    
    while(heap_size != 0){
        int cmp = order;
        if(order == MAX_SORT){
            build_max_heap(temp_list, deg_size, heap_size);
        }else{
            build_min_heap(temp_list, deg_size, heap_size);
        }
        /*Before inserting the term to the final linked list, check if the previous
         * term has the same degree. If they have the same degree <cmp> is 0. In this
         * case add the coefficient to the previous term and free the current term
         * to be added i.e(term_temp[0]). This is done if <cmp == 0>.
        */
        if(result->tail != NULL){
            cmp = compare_degrees(result->tail->deg, temp_list[0]->deg, deg_size);
        }
        if(cmp == 0){
            mpq_add(result->tail->coef, result->tail->coef, temp_list[0]->coef);
            if(mpq_cmp_si(result->tail->coef, 0, 1) == 0){
                result->tail = previous;
                // if(order == MAX_SORT) // TEMPORARY
                //     result->tail->next = NULL;
                result->size--;
                temp_list[0] = temp_list[0]->next; //if the addition result in a zero coefficient needs to update the top of array list
            }
            // else{
            //     term_q *temp = temp_list[0];
            //     temp_list[0] = temp_list[0]->next;
            //     free_linked_list_term_q(temp);
            // }
        }else if(cmp == order){
            previous = result->tail; //previous variable is updated every time a new term is inserted
            if(mpq_cmp_si(temp_list[0]->coef, 0, 1) != 0){ //TEMPORARY
                linked_list_tail_insert_q(result, NULL, temp_list[0]);
            }
            temp_list[0] = temp_list[0]->next;
        }
        if(temp_list[0]==NULL){
            temp_list[0] = temp_list[heap_size-1];
            heap_size--;
        }
        // if(order == MAX_SORT){
        //     build_max_heap(temp_list, deg_size, heap_size);
        // }else{
        //     build_min_heap(temp_list, deg_size, heap_size);
        // }
    }
    
//    linked_list_print_q(result, deg_size);
    return result;
}

linked_list_q *randomly_generated_linked_list_q(int size, int deg_size, int bit_cnt){
    linked_list_q *m_list = create_linked_list_q();
    mpz_t rand_num;
    mpz_t rand_den;
    gmp_randstate_t n_state;
    gmp_randstate_t d_state;
    unsigned long int seed;
    
    seed = time(NULL);
    
    gmp_randinit_default(n_state);
    gmp_randseed_ui(n_state, seed);
    
    gmp_randinit_default(d_state);
    gmp_randseed_ui(d_state, seed*3);
    
    mpz_init(rand_num);
    mpz_init(rand_den);
    
    long int den;
    long int num;
    
    term_q *t;
    degrees *deg;
    mpq_t coef;
    mpq_init(coef);
    
    for(int j = 0; j<size; j++){    
        deg = (degrees*)malloc(sizeof(degrees)*deg_size);
        if(!deg){
            error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
            exit(ERROR_FAILURE);
        }
        for(int i=0; i<deg_size; i++){
            unsigned int val = seed*rand()%4000;
            deg[i] = val;
        }
        
        mpz_urandomb(rand_num, n_state, bit_cnt);
        mpz_urandomb(rand_den, d_state, bit_cnt);
        num = mpz_get_si(rand_num);
        den = mpz_get_si(rand_den);
        
        mpq_set_ui(coef, num, den);
        t = create_term_q(coef, deg, deg_size);
        linked_list_insert_q(m_list, NULL, t);
    }

    gmp_randclear(n_state);
    gmp_randclear(d_state);
    mpz_clear(rand_num);
    mpz_clear(rand_den);
    
    return m_list;
}

linked_list_q* generate_linked_list_from_csv_file(const char *filename){
    linked_list_q *list = create_linked_list_q();
    FILE *f;
    f = fopen(filename, "r");
    if(!f){
        error_print(error_get_string(ERROR_FILE_OPEN), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }

    fseek(f, 0L, SEEK_END);
    int file_size = ftell(f);
    rewind(f);

    char *temp_data = (char*)calloc(file_size, sizeof(char)+1);
    size_t r = fread(temp_data, sizeof(char), file_size, f);
    if(!r){
        error_print(error_get_string(ERROR_READ_WRITE_FILE), __FILE__, __func__, __LINE__);
        fclose(f);
        exit(ERROR_FAILURE);
    }
    fclose(f); //free file
    
    char *pch;
    pch = strtok(temp_data, " \n,");
    long int size = strtol(pch, NULL, 10); //deg_size

    int arr_size = ceil(file_size/(size+2));
    long int *ll = (long int*)malloc(arr_size*sizeof(long int));

    pch = strtok(NULL, " \n,");
    int i=0;
    while(pch != NULL){
        ll[i] = strtol(pch, NULL, 10);
        i++;
        pch = strtok(NULL, " \n,");
    }
    int i_fin = i;
    
    for(int i=0; i<i_fin; i = i+(2+size)){
        mpq_t temp;
        mpq_init(temp);
        mpq_set_si(temp, ll[i], ll[i+1]);
        degrees* temp_deg = generate_long_long_unsigned_int_degrees(size);
        for(int j=0; j<size; j++){
            temp_deg[j] = ll[j+i+2];
        }
        term_q *temp_term =  create_term_q(temp, temp_deg, size);
        linked_list_insert_q(list, NULL, temp_term);
        mpq_clear(temp);
    }
    // // free(ll);
    free(pch);
    free(temp_data);
    free(ll);
    return list;
}

void print_linked_list_to_file(linked_list_q *l, char** var, int numVar, char *filename, int insertVarsAtTheBeginning){
    term_q *temp = l->head;
    
    FILE *f = fopen(filename, "w");
    if(!f){
        error_print(error_get_string(ERROR_FILE_OPEN), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    if(insertVarsAtTheBeginning){
        fprintf(f, "[");
        for(int i=0; i<numVar; i++){
            fprintf(f, "%s",var[i]);
            if(i != numVar-1){
                fprintf(f, ",");
            }
        }
        fprintf(f, "]");
    }

    if(temp == NULL){
        fprintf(f, "%s", "0");
    }
    
    int first = 1;
    int needMult = 0;
    int isConst = 1;
    mpq_t coef;
    mpq_init(coef);
    while(temp != NULL){
        mpq_set(coef, temp->coef);
        isConst = 1;
        if(mpq_cmp_si(temp->coef, 0,1) < 0){
            // fprintf(f, "%s", "-");
        }else if(!first){
            fprintf(f, "%s", "+");
        }

        if(mpq_cmp_si(temp->coef, 1,1) != 0 ){
            if(mpq_cmp_si(temp->coef, -1,1) == 0){
                fprintf(f, "%s", "-");
                needMult = 0;
            }else{
                gmp_fprintf(f, "%Qd", temp->coef);
                needMult = 1;
            }
        }
        // degrees_t *expon = unpacked_degs(temp->elems[i].degs, temp->nvar);
        for(int j=0; j<numVar; j++){
            if(temp->deg[j] == 0){
                continue;
            }
            isConst = 0;
            if(needMult){
                fprintf(f, "%s", "*");
            }
            fprintf(f, "%s", var[j]);
            if(temp->deg[j] > 1){
                fprintf(f, "^%llu", temp->deg[j]);
            }
            needMult = 1;
        }
        temp = temp->next;
        first = 0;
        needMult = 0;
    }
    if(isConst && (mpq_cmp_si(coef, 1,1) == 0)){
        gmp_fprintf(f, "%Qd", coef);
    }
    fprintf(f, "%c", '\0');
    fclose(f);
}


char* print_linked_list_to_string_variable(linked_list_q *list, char** var, int numVar ){
    char *filename = "tempFileToConverToStringVar.txt";
    print_linked_list_to_file(list, var, numVar, filename, 0);
    
    FILE *f = fopen(filename, "r");
    if(!f){
        error_print(error_get_string(ERROR_FILE_OPEN), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }

    fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	rewind(f);

    // char *buf = (char*)malloc(size*sizeof(char)+1);
    char *buf = (char*)calloc(size, sizeof(char)+1);
	size_t r = fread(buf, sizeof(char), size, f);
    buf[size+1] = '\0';
    // printf("printing buffer INSIDE : %s\n", buf);
    fclose(f);
    remove(filename);
    // linked_list_destroy_q(list);
    return buf;
}

char **create_dynamic_str_array(int arrSize, ...){
    char **temp_str_arr = (char**)malloc(arrSize*sizeof(char*));
    if(!temp_str_arr){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    va_list args;
    va_start(args, arrSize);
    for(int i=0; i<arrSize; ++i){
        char *temp_var = strdup(va_arg(args, char*));
        if(!temp_var){
            error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
            exit(ERROR_FAILURE);
        }
        temp_str_arr[i] = (char*)malloc(sizeof(char)*strlen(temp_var)+1);
        strncpy(temp_str_arr[i], temp_var, strlen(temp_var)+1);
        free(temp_var);
    }
    va_end(args);
    
    return temp_str_arr;
}

void free_degrees_variables(char** arr, int size){
    if(arr != NULL){
        for(int i=0; i<size; i++)
            free(arr[i]);
        free(arr);
    }
}

unsigned long int cache_size_byte(){
    char *alllines = (char*)calloc(1024, sizeof(char));
    if(!alllines){
        printf("No file created\n");
        exit(EXIT_FAILURE);
    }
    FILE *cpuinfo;

    if (!(cpuinfo = fopen("/proc/cpuinfo", "r"))) {
        perror("/proc/cpuinfo: fopen");
        return 0;
    }

    fread(alllines, 1024, sizeof(char), cpuinfo);
    alllines[1024] = '\0';
    fclose(cpuinfo);
    char **fin = (char**)malloc(2*sizeof(char*));
    if(!fin){

    }
    while(1){
        char *pch = strstr(alllines, "cache");
        if(pch){
            char *tok = strtok(pch, ":");
            int i = 0;
            while(i < 2){
                tok = strtok(NULL, " :");
                
                fin[i] = malloc(sizeof(char)*strlen(tok)+1);
                memcpy(fin[i], tok, strlen(tok));
                // fin[strlen(tok)+1] = '\0';
                i++;
            }
            break;
        }
    }
    free(alllines);

    unsigned long int cache = 0;
    if(fin != NULL){
        cache = strtol(fin[0], NULL, 10);
        if(strstr(fin[1], "KB"))
            cache =  cache * 1024;
        else if(strstr(fin[1], "MB"))
            cache =  cache * 1048576;
    }
    for(int i=0; i<2; i++){
        free(fin[i]);
    }
    free(fin);
    return cache;
}

unsigned long int appx_base_case_size_based_on_cache_mem(unsigned long int cache_size, int num_vars){
    //approximate assumtion of mpqz_t, 32 bytes since its built from __mpz_struct -> (int, int, _mpz_lib*)
    //_mpz_lib* could vary depending on the size of the number
    int mpq_t_size = 32; 
    int degrees_size = 8 * num_vars;
    int term_q_ptr_size = 8;
    long int total = mpq_t_size + degrees_size + term_q_ptr_size;
    unsigned long int base_case_size = 0;
    if(cache_size != 0)
        base_case_size = cache_size/total;
    else 
        base_case_size = 1;

    return base_case_size;
}