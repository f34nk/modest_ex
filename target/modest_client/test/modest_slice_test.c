
#include "modest_slice.h"
int main(int argc, const char * argv[])
{
  const char *html = "<p>Hello</p><p>World</p>";
  const char *selector = "p:first-of-type, :not(p:first-of-type, body)";
  const char *delimiter = "|";
  char* result = modest_slice_until_selected(html, selector, delimiter);
  printf("%s\n", result);
  if(strcmp(result, "<p>Hello</p>|<p>World</p>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");
  return 0;
}