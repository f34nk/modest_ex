
#include "test_includes.h"
#include "eterm_array.h"

int main(int argc, const char * argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  // test

  eterm_array_t* a = eterm_array_init();
  eterm_array_push(a, erl_mk_binary("hello", strlen("hello")));
  eterm_array_push(a, erl_mk_binary("world", strlen("world")));
  // eterm_array_dump(a, stdout);

  char *result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "hello|world") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }

  eterm_array_destroy(a);
  free(result);

  printf("ok\n");
  return 0;
}