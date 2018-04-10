
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  html_workspace_t* w = html_init();

  const char *html = "<div><p>Hello World</p>World</div>";
  const char *selector = "div p";
  const char *scope = "html";
  char* result = select_and_remove(w, html, selector, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<html><head></head><body><div>World</div></body></html>") != 0){
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