
#include "modest_remove.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>Hello World</p>World</div>";
  const char *selector = "div p";
  const char *scope = "html";
  char* result = modest_select_and_remove(html, selector, scope);
  printf("%s\n", result);
  if(strcmp(result, "<html><head></head><body><div>World</div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");
  return 0;
}