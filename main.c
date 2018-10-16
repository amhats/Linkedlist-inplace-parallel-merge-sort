#include <stdio.h>
#include <time.h>
#include <math.h>
#include "linkedlist.h"
#include <omp.h>
#include <string.h>
#include <stdbool.h>
#include "test.h"
#include <dirent.h>
#include "linked_list_test_framework/test_framework.h"
#include "linked_list_test_framework/maple_evaluate.h"


int count_file_in_dir(char *directory){
    int file_count = 0;
    DIR * dirp;
    struct dirent * entry;

    dirp = opendir(directory); /* There should be error handling after this */
    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_REG) { /* If the entry is a regular file */
            file_count++;
        }
    }
    closedir(dirp);
    return file_count;
}

typedef struct _files{
    int count;
    char** all_files;
}files;

files* get_all_csv_files(char *directory, char *ext){
    int num_files = count_file_in_dir(directory);
    files *csv = malloc(sizeof(files));
    csv->all_files = (char**)malloc(num_files*sizeof(char*)+1);
    if(!csv->all_files){

    }
    csv->count = 0; // count and increament after all file inserted into csv.

    DIR *d;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            p1=strtok(dir->d_name,".");
            p2=strtok(NULL,".");
            if(p2!=NULL)
            {
                ret=strcmp(p2, ext);
                if(ret==0)
                {
                    csv->all_files[csv->count] = (char*)calloc(100, sizeof(char));
                    strncat(csv->all_files[csv->count], directory, strlen(directory));
                    strncat(csv->all_files[csv->count], p1, strlen(p1));
                    strncat(csv->all_files[csv->count], ".csv", 4);
                    int k = strlen(directory) + strlen(p1) + 3;
                    csv->all_files[csv->count][k+1] = '\0';
                    csv->count++;
                }
            }

        }
        closedir(d);
    }
    return csv;
}

void test_all_data(bool maple_assert, long int base_case_size){
    int num_vars = 3;
    files *d = get_all_csv_files("gen_list_py/", "csv");
    unsigned long int base_size = appx_base_case_size_based_on_cache_mem(cache_size_byte(), num_vars);

    if( access( "record_time.csv", F_OK ) == -1 ) {
        record_time_to_file("record_time.csv", true, 0, 0, NULL, 0, 0.0);
    } 

    for(int i=0; i<d->count; i++){
        char *test_file = d->all_files[i];

        test_linked_list_merge_sort_q(test_file, num_vars, NULL, maple_assert);
        test_linked_list_4_way_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size);
        test_linked_list_8_way_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size);
        test_linked_list_16_way_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size);
        test_linked_list_32_way_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size);
        test_linked_list_4_way_heap_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size);   
        test_linked_list_8_way_heap_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size);  
        test_linked_list_16_way_heap_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size); 
        test_linked_list_32_way_heap_merge_sort_q(test_file, num_vars, NULL, maple_assert, base_case_size); 

        test_linked_list_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert);      
        test_linked_list_4_way_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);     
        test_linked_list_8_way_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);    
        test_linked_list_16_way_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);    
        test_linked_list_32_way_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);    
        test_linked_list_4_way_heap_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);     
        test_linked_list_8_way_heap_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);      
        test_linked_list_16_way_heap_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);      
        test_linked_list_32_way_heap_merge_sort_parallel_q(test_file, num_vars, NULL, maple_assert, base_case_size);

        free(d->all_files[i]);
    }
    free(d->all_files);
    free(d);
}

int main(int argc, char** argv) {
    
//    test_create_linked_list_q();
//    test_generate_long_long_unsigned_int_degrees_with_values();
//    test_compare_degrees();
//    test_is_linked_list_empty();
//    test_linked_list_merge_sort();
//    test_build_max_heap();
//    test_build_min_heap();
//    test_max_heap_sort();
//    test_min_heap_sort();

    // linked_list_q *l = test_100();

    

    // test_max_heap_sort(test_file, num_vars);
    // test_build_max_heap(test_file, num_vars);
    // linked_list_destroy_q(l);

    test_all_data(false, 0);
    return (EXIT_SUCCESS);
}

