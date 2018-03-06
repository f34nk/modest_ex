
#include "modest_prepend.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello</p></div>";
  const char *selector = "div p";
  const char *new_html = " World";
  char* result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "") != 0){
    return 1;
  }

  return 0;
}