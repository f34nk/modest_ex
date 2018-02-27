
#include "modest_find.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char *selector = "div > :nth-child(2n+1):not(:has(a))";

  char* result = modest_find(html, selector, "|");
  printf("modest_find: %s\n", result);


  html = "<h1><a>some link</a></h1>";
  selector = "h1 a";

  result = modest_find(html, selector, "|");
  printf("modest_find: %s\n", result);

  return 0;
}