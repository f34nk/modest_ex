
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);
  
  html_workspace_t* w = html_init();

  const char* html = "<p>Hello World</p>";
  eterm_array_t* term_array = eterm_array_init();
  pretty_print(w, html, term_array);
  char* result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  // if(strcmp(result, "\\e[31m<\\e[0m\\e[31mp\\e[0m\\e[31m>\\e[0m\\e[0mHello World\\e[0m\\e[31m</\\e[0m\\e[31mp\\e[0m\\e[31m>\\e[0m\\n") != 0){
  if(strcmp(result, "<p>\n\tHello World\n</p>\n") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  html_destroy(w);
  printf("ok\n");
  return 0;
}