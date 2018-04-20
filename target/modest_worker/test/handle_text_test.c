
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);
  
  html_workspace_t* w = html_init();

  const char *html = "<div>Hello <p>World</p></div>";
  char* result = get_text(w, html, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "Hello |World") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<div><p>Hello World</p></div>";
  result = select_and_get_text(w, html, "div p", "|");
  printf("-> %s\n", result);
  if(strcmp(result, "Hello World") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<div><p></p></div>";
  const char *scope = "body_children";
  result = select_and_set_text(w, html, "div p", "Hello World", scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<div><p>Hello World</p></div>") != 0){
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