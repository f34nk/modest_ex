
#include "modest_replace.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div p";
  const char *new_html = "<p>World</p>";
  const char *scope = "body_children";
  char* result = modest_select_and_replace(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");

  html = "<div><p>Hello</p></div>";
  selector = "div p";
  new_html = "World";
  result = modest_select_and_replace(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div>World</div>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");

  html = "<html><head></head><body></body></html>";
  selector = "body";
  new_html = "<p>Hello World</p>";
  scope = "html";
  result = modest_select_and_replace(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<html><head></head><p>Hello World</p></html>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");

  return 0;
}