
#include "modest_position.h"
int main(int argc, const char * argv[])
{
  const char *html = "<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>";
  const char *selector = "ul";
  const char *delimiter = "|";
  const char *result = modest_selected_position(html, selector, delimiter);
  printf("1: %s\n", result);
  if(strcmp(result, "3") != 0){
    printf("Failed\n");
    return 1;
  }

  selector = "p";
  result = modest_selected_position(html, selector, delimiter);
  printf("2: %s\n", result);
  if(strcmp(result, "2|4|5") != 0){
    printf("Failed\n");
    return 1;
  }

  selector = "div";
  result = modest_selected_position(html, selector, delimiter);
  printf("3: %s\n", result);
  if(strcmp(result, "") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p>Hello</p><div></div><p>World</p>";
  selector = "p";
  result = modest_selected_position(html, selector, delimiter);
  printf("4: %s\n", result);
  if(strcmp(result, "1|3") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}