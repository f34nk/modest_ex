
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);
  
  html_workspace_t* w = html_init();

  const char* html = "<p>Hello</p><p>World</p>";
  const char* selector = "p";
  const char* new_html = "<div class=\"wrapper\"></div>";
  const char* scope = "body_children";
  vec_eterm_t term_array; 
  eterm_vec_init(&term_array);
  select_and_wrap(w, html, selector, new_html, scope, &term_array);
  char* result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<div class=\"wrapper\"><p>Hello</p><p>World</p></div>") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html = "<p>Hello</p><p>World</p>";
  selector = "p";
  new_html = "Lorem ipsum";
  select_and_wrap(w, html, selector, new_html, scope, &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "Lorem ipsum<p>Hello</p><p>World</p>") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);
  
  // TODO: Text node is not selected here.
  // not implemented yet.
  // html = "Hello World";
  // selector = "*";
  // new_html = "<div class=\"wrapper\"></div>";
  // result = select_and_wrap(html, selector, new_html, scope);
  // printf("-> %s\n", result);
  // if(strcmp(result, "<div class=\"wrapper\">Hello World</div") != 0){
  //   printf("Failed\n");
  //   html_free(result);
  // html_destroy(w);
  // TEST_ERROR
  // return 1;
  // }

  html_destroy(w);
  printf("ok\n");
  return 0;
}