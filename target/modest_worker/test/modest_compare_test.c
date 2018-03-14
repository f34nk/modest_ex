
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
  printf("ok\n");
  return 0;
}