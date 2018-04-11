#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "eterm_array.h"

eterm_array_t* eterm_array_init()
{
  size_t array_size = sizeof(struct eterm_array);
  eterm_array_t* array = NULL;
  array = (eterm_array_t*)malloc(array_size);
  if(array == NULL) {
    fprintf(stderr, "eterm_array_init() - Failed to allocate array.\n");
    return NULL;
  }
  array->data = (ETERM**)malloc(0);
  array->size = 0;
  return array;
}

bool eterm_array_push(eterm_array_t* array, ETERM* eterm)
{
  ETERM** data = array->data;
  int prev = array->size;

  // realloc data
  ETERM** new_data = (ETERM**)realloc(data, prev + 1 * sizeof(ETERM*));
  if(new_data == NULL) {
    // User must free data with eterm_array_destroy()
    fprintf(stderr, "eterm_array_push() - Failed to realloc data\n");
    return false;
  }
  data = new_data;

  // allocate new string memory
  data[prev] = (ETERM*)malloc(1 * sizeof(ETERM*));
  if(data[prev] == NULL) {
    // User must free data with eterm_array_destroy()
    fprintf(stderr, "eterm_array_push() - Failed to malloc string memory\n");
    return false;
  }

  // assign term
  data[prev] = eterm;

  // update pointers
  array->data = data;
  array->size = prev + 1;

  return true;
}

bool eterm_array_copy(eterm_array_t* array, const ETERM** data, int length)
{
  for (int i = 0; i < length; ++i) {
    if(eterm_array_push(array, (ETERM*)data[i]) == false) {
      return false;
    }
  }
  return true;
}

void eterm_array_destroy(eterm_array_t* array)
{
  for (int i = 0; i < array->size; ++i) {
    erl_free_term(array->data[i]);
  }
  free(array->data);
  array->data = NULL;
  array->size = 0;
}

void eterm_array_dump(eterm_array_t* array, FILE* stream)
{
  for (int i = 0; i < array->size; ++i) {
    erl_print_term(stream, array->data[i]);
  }
  if(array->size > 0) {
    fprintf(stream, "\n");
  }
}

