
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  html_workspace_t* w = html_init();

  const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char *scope = "html";
  char* result = serialize(w, html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<html><head></head><body><div><p id=\"p1\"></p><p id=\"p2\"></p><p id=\"p3\"><a>link</a></p><p id=\"p4\"></p><p id=\"p5\"></p><p id=\"p6\"></p></div></body></html>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<span>Hello World</span";
  scope = "body";
  result = serialize(w, html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<body><span>Hello World</span></body>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<span Hello World";
  scope = "body_children";
  result = serialize(w, html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<span hello=\"\" world=\"\"></span>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "";
  scope = "html";
  result = serialize(w, html, scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<html><head></head><body></body></html>") != 0){
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