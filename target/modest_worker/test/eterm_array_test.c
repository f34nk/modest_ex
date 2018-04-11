
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
  eterm_array_dump(a, stdout);
  eterm_array_destroy(a);

  printf("ok\n");
  return 0;
}