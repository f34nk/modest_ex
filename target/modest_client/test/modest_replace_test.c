
#include "modest_replace.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div p";
  const char *new_html = "<div><p>World</p></div>";
  char* result = modest_select_and_replace(html, selector);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");
  return 0;
}