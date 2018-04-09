
#include "modest_pretty_print.h"
int main(int argc, const char * argv[])
{
  const char *html = "<p>Hello World</p>";
  char* result = modest_pretty_print(html);
  printf("1: %s\n", result);
  if(strcmp(result, "\\e[31m<\\e[0m\\e[31mp\\e[0m\\e[31m>\\e[0m\\e[0mHello World\\e[0m\\e[31m</\\e[0m\\e[31mp\\e[0m\\e[31m>\\e[0m\\n") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}