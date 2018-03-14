
#include "modest_compare.h"
int main(int argc, const char * argv[])
{
  const char *html1 = "<div>Hello</div>";
  const char *html2 = "<div>Hello<span>World</span></div>";
  const char *scope = "body_children";
  char* result = modest_compare(html1, html2, scope);
  printf("1: %s\n", result);
  // if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }
  
  html1 = "<div>Hello<span>World</span></div><div>Other</div>";
  html2 = "<div>Hello</div><div>Other</div>";
  // scope = "body_children";
  result = modest_compare(html1, html2, scope);
  printf("2: %s\n", result);
  // if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }
  
  html1 = "<div>Hello</div><div>World</div>";
  html2 = "<div>Hello<span>Other</span></div><div>World</div>";
  // scope = "body_children";
  result = modest_compare(html1, html2, scope);
  printf("3: %s\n", result);
  // if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  html1 = "<div>Hello<ul><li>Coffee</li><li>Tea<ul><li>Black tea</li><ul><li>Green tea</li><li>Blue tea</li></ul></ul></li><li>Milk</li></ul></div>";
  html2 = "<div>Hello<ul><li>Coffee</li><li>Tea<ul><li>Black tea</li><ul><li>Green tea</li></ul></ul></li><li>Milk</li></ul></div>";
  // scope = "body_children";
  result = modest_compare(html1, html2, scope);
  printf("4: %s\n", result);
  // if(strcmp(result, "<div><p>Hello</p><p>World</p></div>") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }
  
  printf("ok\n");
  return 0;
}