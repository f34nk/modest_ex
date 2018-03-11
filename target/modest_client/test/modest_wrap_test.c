
#include "modest_wrap.h"
int main(int argc, const char * argv[])
{
  const char *html = "<p>Hello</p><p>World</p>";
  const char *selector = "p";
  const char *new_html = "<div class=\"wrapper\"></div>";
  const char *scope = "body_children";
  char* result = modest_select_and_wrap(html, selector, new_html, scope);
  printf("1: %s\n", result);
  if(strcmp(result, "<div class=\"wrapper\"><p>Hello</p></div><div class=\"wrapper\"><p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p>Hello</p><p>World</p>";
  selector = "p";
  new_html = "Lorem ipsum";
  result = modest_select_and_wrap(html, selector, new_html, scope);
  printf("2: %s\n", result);
  if(strcmp(result, "<p>Hello</p><p>World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  // TODO: Text node is not selected here.
  // not implemented yet.
  // html = "Hello World";
  // selector = "*";
  // new_html = "<div class=\"wrapper\"></div>";
  // result = modest_select_and_wrap(html, selector, new_html, scope);
  // printf("2: %s\n", result);
  // if(strcmp(result, "<div class=\"wrapper\">Hello World</div") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  printf("ok\n");
  return 0;
}