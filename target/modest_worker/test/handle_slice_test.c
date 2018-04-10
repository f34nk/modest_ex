
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  html_workspace_t* w = html_init();

  const char *html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char *selector = "body > *"; // all direct children
  int start = 0;
  int end = -1;
  const char *delimiter = "|";
  char* result = slice_selected(w, html, selector, start, end, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>|<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  start = 0;
  end = 3;
  result = slice_selected(w, html, selector, start, end, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  start = 3;
  end = -1;
  result = slice_selected(w, html, selector, start, end, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  start = 0;
  end = -1;
  result = slice_selected(w, html, selector, start, end, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>|<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html_destroy(w);
  printf("ok\n");
  return 0;
}