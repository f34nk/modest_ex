
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  html_workspace_t* w = html_init();

  const char* html = "<div><p>Hello</p></div>";
  const char* selector = "div p";
  const char* new_html = "<p>World</p>";
  const char* scope = "body_children";
  eterm_array_t* term_array = eterm_array_init();
  select_and_insert_after(w, html, selector, new_html, scope, term_array);
  char* result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  html = "<div><p>Hello</p></div>";
  selector = "div p";
  new_html = "World";
  term_array = eterm_array_init();
  select_and_insert_after(w, html, selector, new_html, scope, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<div><p>Hello</p>World</div>") != 0) {
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