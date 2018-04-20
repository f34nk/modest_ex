
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);
  
  html_workspace_t* w = html_init();

  const char *html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char *selector = "body > *"; // all direct children
  int start = 0;
  int end = -1;
  const char *delimiter = "|";
  eterm_array_t* term_array = eterm_array_init();
  slice_selected(w, html, selector, start, end, delimiter, term_array);
  char* result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>|<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  start = 0;
  end = 3;
  term_array = eterm_array_init();
  slice_selected(w, html, selector, start, end, delimiter, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>") != 0){
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  start = 3;
  end = -1;
  term_array = eterm_array_init();
  slice_selected(w, html, selector, start, end, delimiter, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  start = 0;
  end = -1;
  term_array = eterm_array_init();
  slice_selected(w, html, selector, start, end, delimiter, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>|<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
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