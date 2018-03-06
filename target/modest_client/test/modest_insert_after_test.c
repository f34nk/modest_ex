
#include "modest_insert_after.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div p";
  const char *new_html = "<p>World</p>";
  char* result = modest_select_and_insert_after(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>Hello</p></div>";
  selector = "div p";
  new_html = "World";
  result = modest_select_and_insert_after(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p>World</div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}