
#include "modest_append.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div";
  const char *new_html = "<p>World</p>";
  char* result = modest_select_and_append(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>Hello</p></div>";
  selector = "div";
  new_html = "World";
  result = modest_select_and_append(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p>World</div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>Hello</p></div>";
  selector = "div p";
  new_html = " World";
  result = modest_select_and_append(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><input type=\"radio\"></div>";
  selector = "div input";
  new_html = "This will not be appended";
  result = modest_select_and_append(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><input type=\"radio\"></input></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}