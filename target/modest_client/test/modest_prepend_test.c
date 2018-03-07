
#include "modest_prepend.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p>World</p></div>";
  const char *selector = "div";
  const char *new_html = "<p>Hello</p>";
  const char *scope = "body_children";
  char* result = modest_select_and_prepend(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "";
  selector = "*";
  new_html = "<p>Hello World</p>";
  result = modest_select_and_prepend(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<p>Hello World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "";
  selector = "*";
  new_html = "Hello World";
  result = modest_select_and_prepend(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "Hello World") != 0){
    printf("Failed\n");
    return 1;
  }
  
  html = "<div><p>World</p></div>";
  selector = "div p";
  new_html = "Hello ";
  result = modest_select_and_prepend(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><p>Hello World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><p>World</p></div>";
  selector = "div";
  new_html = "Hello";
  result = modest_select_and_prepend(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div>Hello<p>World</p></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><input type=\"radio\"></div>";
  selector = "div input";
  new_html = "Radio Button";
  result = modest_select_and_prepend(html, selector, new_html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<div><input type=\"radio\">Radio Button</input></div>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}