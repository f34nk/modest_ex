
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  html_workspace_t* w = html_init();

  const char* html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char* selector = "ul";
  const char* delimiter = "|";
  vec_eterm_t term_array; 
  eterm_vec_init(&term_array);
  selected_position(w, html, selector, delimiter, &term_array);
  char* result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "3") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  selector = "p";
  eterm_vec_init(&term_array);
  selected_position(w, html, selector, delimiter, &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "2|4|5") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html = "<p>Hello</p><div></div><p>World</p>";
  selector = "p";
  eterm_vec_init(&term_array);
  selected_position(w, html, selector, delimiter, &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "1|3") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  // TODO: handle empty html string
  // html = "";
  // selector = "div";
  // eterm_vec_init(&term_array);
  // selected_position(w, html, selector, delimiter, &term_array);
  // result = eterm_vec_join(&term_array, "|");
  // if(result != NULL) {
  //   printf("-> %s\n", result);
  //   eterm_vec_destroy(&term_array);
  //   free(result);
  //   html_destroy(w);
  //   TEST_ERROR
  //   return 1;
  // }
  // else {
  //   printf("-> NULL\n");
  // }
  // eterm_vec_destroy(&term_array);

  html_destroy(w);
  printf("ok\n");
  return 0;
}