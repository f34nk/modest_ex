
#include "modest_serialize.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  char* result = modest_serialize(html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><div><p id=\"p1\"></p><p id=\"p2\"></p><p id=\"p3\"><a>link</a></p><p id=\"p4\"></p><p id=\"p5\"></p><p id=\"p6\"></p></div></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<span>Hello World</span";
  result = modest_serialize(html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><span>Hello World</span></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<span Hello World";
  result = modest_serialize(html);
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><span hello=\"\" world=\"\"></span></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }
  printf("ok\n");
  return 0;
}