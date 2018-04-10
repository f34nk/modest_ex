
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  html_workspace_t* w = html_init();

  const char *html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char *selector = "ul";
  const char *delimiter = "|";
  const char *result = selected_position(w, html, selector, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "3") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  selector = "p";
  result = selected_position(w, html, selector, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "2|4|5") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<p>Hello</p><div></div><p>World</p>";
  selector = "p";
  result = selected_position(w, html, selector, delimiter);
  printf("-> %s\n", result);
  if(strcmp(result, "1|3") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "";
  selector = "div";
  result = selected_position(w, html, selector, delimiter);
  printf("-> %s\n", result);
  if(result != NULL){
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