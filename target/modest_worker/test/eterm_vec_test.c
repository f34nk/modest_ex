
#include "test_includes.h"
#include "eterm_vec.h"
/*
To check for memory leaks execute test with valgrind.

  valgrind --leak-check=yes target/modest_worker/build/test/eterm_vec_test

*/
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  vec_eterm_t v;
  eterm_vec_init(&v);

  eterm_vec_push(&v, erl_mk_binary("Lorem", strlen("Lorem")));
  eterm_vec_push(&v, erl_mk_binary("ipsum", strlen("ipsum")));
  eterm_vec_push(&v, erl_mk_binary("dolor", strlen("dolor")));
  eterm_vec_push(&v, erl_mk_binary("sit", strlen("sit")));
  eterm_vec_push(&v, erl_mk_binary("amet", strlen("amet")));
  eterm_vec_push(&v, erl_mk_binary("consectetur", strlen("consectetur")));

  eterm_vec_dump(&v, stdout);

  char* result = eterm_vec_join(&v, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "Lorem|ipsum|dolor|sit|amet|consectetur") != 0) {
    eterm_vec_destroy(&v);
    free(result);
    TEST_ERROR
    return 1;
  }

  eterm_vec_destroy(&v);
  free(result);

  printf("ok\n");
  return 0;
}