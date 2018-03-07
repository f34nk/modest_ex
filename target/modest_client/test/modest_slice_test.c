
#include "modest_slice.h"
int main(int argc, const char * argv[])
{
  const char *html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char *selector = "h1, ul";
  const char *delimiter = "|";
  const char *scope = "body";
  char* result = modest_slice_until_selected(html, selector, delimiter, scope);
  printf("%s\n", result);
  if(strcmp(result, "asdasd") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");
  return 0;
}