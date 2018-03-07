
#include "modest_slice.h"
int main(int argc, const char * argv[])
{
  const char *html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char *selector = "> *";
  int start = 0;
  int end = -1;
  const char *delimiter = "|";
  const char *scope = "body_children";
  char* result = modest_slice_selected(html, selector, start, end, delimiter, scope);
  printf("1: %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>|<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  start = 0;
  end = 3;
  result = modest_slice_selected(html, selector, start, end, delimiter, scope);
  printf("2: %s\n", result);
  if(strcmp(result, "<h1>Lorem ipsum</h1>|<p>dolor sit amet</p>|<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>") != 0){
    printf("Failed\n");
    return 1;
  }

  start = 3;
  end = -1;
  result = modest_slice_selected(html, selector, start, end, delimiter, scope);
  printf("3: %s\n", result);
  if(strcmp(result, "<p>Sed ut perspiciatis</p>|<p>unde omnis iste natus</p>") != 0){
    printf("Failed\n");
    return 1;
  }
  
  printf("ok\n");
  return 0;
}