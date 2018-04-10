
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  html_workspace_t* w = html_init();

  const char* html = "<p>Hello World</p>";
  char* result = pretty_print(w, html);
  printf("-> %s\n", result);
  // if(strcmp(result, "\\e[31m<\\e[0m\\e[31mp\\e[0m\\e[31m>\\e[0m\\e[0mHello World\\e[0m\\e[31m</\\e[0m\\e[31mp\\e[0m\\e[31m>\\e[0m\\n") != 0){
  if(strcmp(result, "<p>\n\tHello World\n</p>\n") != 0) {
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html_destroy(w);
  printf("ok\n");
  return 0;
}