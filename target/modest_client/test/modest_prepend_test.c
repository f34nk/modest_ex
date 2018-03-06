
#include "modest_prepend.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>World</p></div>";
  const char *selector = "div";
  const char *new_html = "<p>Hello</p>";
  char* result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello</p><p>World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<html><head></head><body></body></html>";
  selector = "body";
  new_html = "<p>Hello World</p>";
  result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><p>Hello World</p></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<html><head></head><body></body></html>";
  selector = "body";
  new_html = "Hello World";
  result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body>Hello World</body></html>") != 0){
    printf("Failed\n");
    return 1;
  }
  
  html = "<div><p>World</p></div>";
  selector = "div p";
  new_html = "Hello ";
  result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>World</p></div>";
  selector = "div";
  new_html = "Hello";
  result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div>Hello<p>World</p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><input type=\"radio\"></div>";
  selector = "div input";
  new_html = "Radio Button";
  result = modest_select_and_prepend(html, selector, new_html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><input type=\"radio\">Radio Button</input></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}