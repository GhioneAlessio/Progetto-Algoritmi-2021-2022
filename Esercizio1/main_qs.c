#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quicksort.h"

struct record{
  int id;
  char *field1;
  int field2;
  double field3;
};

//It takes as input two pointers to struct record.
//It returns 1 if the integer field of the first record is less than 
//the integer field of the second one (0 otherwise)
static int precedes_record_int_field(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if(rec1_p->id < rec2_p->id){
    return(1);
  }
  return(0);
}


///It takes as input two pointers to struct record.
//It returns 1 iff the string field of the first record is less than 
//the string field of the second one (0 otherwise)
/*
static int precedes_record_string_field(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if(strcmp(rec1_p->string_field,rec2_p->string_field)<0){
    return(1);
  }
  return(0);
}
*/

static  void free_array(QuickSort* array) {
  unsigned long  el_num =  quick_sort_size(array);
  for(unsigned long i=0;i<el_num;i++){
    struct record *array_element = (struct record *)quick_sort_get(array, i);
    free(array_element->field1);
    free(array_element);
  }
  quick_sort_free_memory(array);
}

static  void print_array(QuickSort* array){
  unsigned long el_num =  quick_sort_size(array);
  struct record *array_element;
  
  printf("\nQUICKSORT ARRAY OF RECORDS\n");
  
  for(unsigned long i=0;i<el_num;i++){
    array_element = (struct record *)quick_sort_get(array, i);
    printf("<%d,%s, %d, %f>\n",array_element->id, array_element->field1, array_element->field2, array_element->field3); 
  }
}

static void load_array(const char* file_name, QuickSort* array){
  char *read_line_p;
  char buffer[1024];
  int buf_size = 1024;
  FILE *fp;
  printf("\nLoading data from file...\n");
  fp = fopen(file_name,"r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the file");
    exit(EXIT_FAILURE);
  }
  while(fgets(buffer,buf_size,fp) != NULL){  
    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read line");
      exit(EXIT_FAILURE);
    }   
    strcpy(read_line_p,buffer);   
    char *id_in_read_line_p = strtok(read_line_p,",");
    char *field1_in_read_line_p = strtok(NULL,",");
    char *field2_in_read_line_p = strtok(NULL,",");  
    char *field3_in_read_line_p = strtok(NULL,",");  

    int id = atoi(id_in_read_line_p);

    char *field1 = malloc((strlen(field1_in_read_line_p)+1)*sizeof(char));
    if(field1 == NULL){
      fprintf(stderr,"main: unable to allocate memory for the field1 of the read record");
      exit(EXIT_FAILURE);
    }  
    strcpy(field1,field1_in_read_line_p);
    
    int field2 = atoi(field2_in_read_line_p);
    double field3 = atof(field3_in_read_line_p); 
    struct record *record_p = malloc(sizeof(struct record));
    if(record_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }   
    record_p->id = id;
    record_p->field1 = field1;
    record_p->field2 = field2;
    record_p->field3 = field3;
    quick_sort_add(array, (void*)record_p);
    free(read_line_p);
  }
  fclose(fp);
  printf("\nData loaded\n");
}

static  void test_with_comparison_function(const char* file_name, int (*compare)(void*, void*)) {
  QuickSort* array = quick_sort_create(compare);
  load_array(file_name, array);
  quickSort(array, 0, quick_sort_size(array));
  print_array(array);
  free_array(array);
}

//It should be invoked with one parameter specifying the filepath of the data file
int main(int argc, char const *argv[]) {
  if(argc < 2) {
    printf("Usage: quick_sort_main <file_name>\n");
    exit(EXIT_FAILURE);
  }
 // test_with_comparison_function(argv[1], precedes_record_int_field);
 // test_with_comparison_function(argv[1], precedes_record_string_field);   
  
 QuickSort* array = quick_sort_create(precedes_record_int_field);
  load_array(argv[1], array);
//  quickSort(array, 0, quick_sort_size(array));
  print_array(array);
  free_array(array);

  return (EXIT_SUCCESS);
}




