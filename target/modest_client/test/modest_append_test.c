
#include "modest_append.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div";
  const char *new_html = "<p>World</p>";
  char* result = modest_select_and_append(html, selector, new_html);
  // printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>") != 0){
    return 1;
  }

  return 0;
}