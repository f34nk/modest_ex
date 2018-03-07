
#include "modest_text.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div>Hello <p>World</p></div>";
  char* result = modest_get_text(html, "|");
  printf("%s\n", result);
  if(strcmp(result, "Hello |World") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>Hello World</p></div>";
  result = modest_select_and_get_text(html, "div p", "|");
  printf("%s\n", result);
  if(strcmp(result, "Hello World") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p></p></div>";
  const char *scope = "body_children";
  result = modest_select_and_set_text(html, "div p", "Hello World", scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>Hello World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}