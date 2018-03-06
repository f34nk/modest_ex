
#include "modest_insert_after.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div p";
  const char *new_html = "<p>World</p>";
  const char *scope = "body_first_child";
  char* result = modest_select_and_insert_after(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>Hello</p></div>";
  selector = "div p";
  new_html = "World";
  result = modest_select_and_insert_after(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>Hello</p>World</div>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}