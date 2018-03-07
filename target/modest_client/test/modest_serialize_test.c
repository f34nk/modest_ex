
#include "modest_serialize.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char *scope = "html";
  char* result = modest_serialize(html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<html><head></head><body><div><p id=\"p1\"></p><p id=\"p2\"></p><p id=\"p3\"><a>link</a></p><p id=\"p4\"></p><p id=\"p5\"></p><p id=\"p6\"></p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<span>Hello World</span";
  scope = "body";
  result = modest_serialize(html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<body><span>Hello World</span></body>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<span Hello World";
  scope = "body_children";
  result = modest_serialize(html, scope);
  printf("%s\n", result);
  if(strcmp(result, "<span hello=\"\" world=\"\"></span>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");
  return 0;
}