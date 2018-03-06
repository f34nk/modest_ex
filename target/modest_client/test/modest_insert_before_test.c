
#include "modest_insert_before.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>World</p></div>";
  const char *selector = "div";
  const char *new_html = "<p>Hello</p>";
  char* result = modest_select_and_insert_before(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  // html = "<div><p>World</p></div>";
  // selector = "div p";
  // new_html = "Hello ";
  // result = modest_select_and_insert_before(html, selector, new_html);
  // printf("%s\n", result);
  // if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello World</p></div></body></html>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  // html = "<div><p>World</p></div>";
  // selector = "div";
  // new_html = "Hello";
  // result = modest_select_and_insert_before(html, selector, new_html);
  // printf("%s\n", result);
  // if(strcmp(result, "<-undef><html><head></head><body><div>Hello<p>World</p></div></body></html>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  // html = "<div><input type=\"radio\"></div>";
  // selector = "div input";
  // new_html = "This will not be prepended";
  // result = modest_select_and_insert_before(html, selector, new_html);
  // printf("%s\n", result);
  // if(strcmp(result, "<-undef><html><head></head><body><div><input type=\"radio\"></input></div></body></html>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  printf("ok\n");
  return 0;
}