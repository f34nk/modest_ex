
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);
  
  html_workspace_t* w = html_init();

  const char *html = "<div><p>Hello World</p>World</div>";
  const char *selector = "div p";
  const char *scope = "html";
  vec_eterm_t term_array; 
  eterm_vec_init(&term_array);
  select_and_remove(w, html, selector, scope, &term_array);
  char* result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<html><head></head><body><div>World</div></body></html>") != 0){
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html_destroy(w);
  printf("ok\n");
  return 0;
}