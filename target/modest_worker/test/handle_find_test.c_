
#include "modest_find.h"
int main(int argc, const char * argv[])
{
  int i = 0;
  const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char *selector = "div > :nth-child(2n+1):not(:has(a))";
  const char *scope = "body_children";
  char* result = modest_find(html, selector, "|", scope);
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<p id=\"p1\"></p>|<p id=\"p5\"></p>") != 0){
    printf("Failed\n");
    return 1;
  }

  // html = "<div><div><a>Hello</a></div><div><a>World</a></div></div>";
  // selector = "div:first-of-type a";
  // result = modest_find(html, selector, "|", scope);
  // printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  // if(strcmp(result, "") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  // html = "<div><div><a>Hello</a></div><div><a>World</a></div></div>";
  // selector = "div:last-of-type a";
  // result = modest_find(html, selector, "|", scope);
  // printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  // if(strcmp(result, "") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  html = "<h1><a>some link</a></h1>";
  selector = "h1 a";
  result = modest_find(html, selector, "|", scope);
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<a>some link</a>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p>Hello</p><p>World</p>";
  selector = "p";
  result = modest_find(html, selector, "|", scope);
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<p>Hello</p>|<p>World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<div><input type=\"radio\"></div>";
  selector = "div input";
  result = modest_find(html, selector, "|", scope);
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<input type=\"radio\"></input>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>";
  selector = "*";
  result = modest_find(html, selector, "|", scope);
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<h1>Hello</h1>|<p>World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>";
  selector = "*";
  result = modest_find(html, selector, "|", "body");
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<body><h1>Hello</h1><p>World</p></body>|<h1>Hello</h1>|<p>World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>";
  selector = "*";
  result = modest_find(html, selector, "|", "head");
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<head></head>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>";
  selector = "*";
  result = modest_find(html, selector, "|", "html");
  printf("%d:\nhtml = %s\nselector = %s\nscope = %s\nresult = %s\n", i+=1, html, selector, scope, result);
  if(strcmp(result, "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>|<head></head>|<body><h1>Hello</h1><p>World</p></body>|<h1>Hello</h1>|<p>World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  // NOT SUPPORTED RIGHT NOW
  // html = "<p><span id=\"hello\">Hello</span></p><p><span name=\"value\">World</span></p>";
  // selector = "[name!=\"value\"]";
  // result = modest_find(html, selector, "|");
  // printf("8: %s\n", result);
  // if(strcmp(result, "<a>some link</a>") != 0){
  //   return 1;
  // }

  printf("ok\n");
  return 0;
}