
#include "modest_insert_before.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>World</p></div>";
  const char *selector = "div p";
  const char *new_html = "<p>Hello</p>";
  const char *scope = "body_children";
  char* result = modest_select_and_insert_before(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>World</p></div>";
  selector = "div p";
  new_html = "Hello";
  result = modest_select_and_insert_before(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div>Hello<p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}