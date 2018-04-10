
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  html_workspace_t* w = html_init();

  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div p";
  const char *new_html = "<p>World</p>";
  const char *scope = "body_children";
  char* result = select_and_replace(w, html, selector, new_html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<div><p>World</p></div>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);
  
  html = "<div><p>Hello</p></div>";
  selector = "div p";
  new_html = "World";
  result = select_and_replace(w, html, selector, new_html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<div>World</div>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<html><head></head><body></body></html>";
  selector = "body";
  new_html = "<p>Hello World</p>";
  scope = "html";
  result = select_and_replace(w, html, selector, new_html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<html><head></head><p>Hello World</p></html>") != 0){
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