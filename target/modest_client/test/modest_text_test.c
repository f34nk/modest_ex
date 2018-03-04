
#include "modest_text.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div>Hello World</div>";
  char* result = modest_get_text(html);
  if(strcmp(result, "Hello World") != 0){
    return 1;
  }

  html = "<div><p>Hello World</p></div>";
  result = modest_get_text(html, "div p");
  if(strcmp(result, "Hello World") != 0){
    return 1;
  }

  html = "<div></div>";
  result = modest_set_text(html, "Hello World");
  if(strcmp(result, "<-undef><html><head></head><body><div>Hello World</div></body></html>") != 0){
    return 1;
  }

  html = "<div><p></p></div>";
  result = modest_set_text(html, "div p", "Hello World");
  if(strcmp(result, "<-undef><html><head></head><body><div><p>Hello World</p></div></body></html>") != 0){
    return 1;
  }

  return 0;
}