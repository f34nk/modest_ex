
#include "modest_find.h"
int main(int argc, const char * argv[])
{
  const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char *selector = "div > :nth-child(2n+1):not(:has(a))";

  char* result = modest_find(html, selector, "|");
  if(strcmp(result, "<p id=\"p1\"></p>|<p id=\"p5\"></p>") != 0){
    return 1;
  }

  html = "<h1><a>some link</a></h1>";
  selector = "h1 a";
  result = modest_find(html, selector, "|");
  if(strcmp(result, "<a>some link</a>") != 0){
    return 1;
  }

  // html = "<p><span id=\"hello\">Hello</span></p><p><span name=\"value\">World</span></p>";
  // selector = "[name!=\"value\"]";
  // result = modest_find(html, selector, "|");
  // printf("%s\n", result);
  // if(strcmp(result, "<a>some link</a>") != 0){
  //   return 1;
  // }

  return 0;
}