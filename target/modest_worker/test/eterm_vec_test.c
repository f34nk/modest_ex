
#include "test_includes.h"
#include "eterm_vec.h"
/*
To check for memory leaks execute test with term_arrayalgrind.

  term_arrayalgrind --leak-check=yes target/modest_worker/build/test/eterm_vec_test

*/
int main(int argc, const char* argterm_array[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  vec_eterm_t term_array;
  eterm_vec_init(&term_array);

  eterm_vec_push(&term_array, erl_mk_binary("Lorem", strlen("Lorem")));
  eterm_vec_push(&term_array, erl_mk_binary("ipsum", strlen("ipsum")));
  eterm_vec_push(&term_array, erl_mk_binary("dolor", strlen("dolor")));
  eterm_vec_push(&term_array, erl_mk_binary("sit", strlen("sit")));
  eterm_vec_push(&term_array, erl_mk_binary("amet", strlen("amet")));
  eterm_vec_push(&term_array, erl_mk_binary("consectetur", strlen("consectetur")));

  eterm_vec_dump(&term_array, stdout);

  char* result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "Lorem|ipsum|dolor|sit|amet|consectetur") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    TEST_ERROR
    return 1;
  }
  free(result);

  ETERM* term_list = eterm_vec_to_list(term_array);
  result = eterm_to_string(term_list);
  printf("-> %s\n", result);
  if(strcmp(result, "[#Bin<Lorem>,#Bin<ipsum>,#Bin<dolor>,#Bin<sit>,#Bin<amet>,#Bin<consectetur>]") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    erl_free_term(term_list);
    TEST_ERROR
    return 1;
  }
  free(result);

  ETERM* formatted = erl_format("{formatted, ~w}", term_list);
  result = eterm_to_string(formatted);
  printf("-> %s\n", result);
  if(strcmp(result, "{formatted,[#Bin<Lorem>,#Bin<ipsum>,#Bin<dolor>,#Bin<sit>,#Bin<amet>,#Bin<consectetur>]}") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    erl_free_term(term_list);
    erl_free_term(formatted);
    TEST_ERROR
    return 1;
  }
  free(result);

  erl_free_term(term_list);
  erl_free_term(formatted);

  eterm_vec_destroy(&term_array);

  printf("ok\n");
  return 0;
}