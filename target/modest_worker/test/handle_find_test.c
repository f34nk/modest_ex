
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  html_workspace_t* w = html_init();

  int i = 0;
  const char* html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char* selector = "div > :nth-child(2n+1):not(:has(a))";
  const char* delimiter = "|";
  const char* scope_name = "html";
  eterm_array_t* term_array = eterm_array_init();
  find(w, html, selector, delimiter, scope_name, term_array);
  char* result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p id=\"p1\"></p>|<p id=\"p5\"></p>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  // html = "<div><div><a>Hello</a></div><div><a>World</a></div></div>";
  // selector = "div:first-of-type a";
  // result = find(w, html, selector, "|", scope_name);
  // printf("-> %s\n", result);
  // if(strcmp(result, "") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  // html = "<div><div><a>Hello</a></div><div><a>World</a></div></div>";
  // selector = "div:last-of-type a";
  // result = find(w, html, selector, "|", scope_name);
  // printf("-> %s\n", result);
  // if(strcmp(result, "") != 0){
  //   printf("Failed\n");
  //   return 1;
  // }

  html = "<h1><a>some link</a></h1>";
  selector = "h1 a";
  term_array = eterm_array_init();
  find(w, html, selector, delimiter, scope_name, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<a>some link</a>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  html = "<p>Hello</p><p>World</p>";
  selector = "p";
  term_array = eterm_array_init();
  find(w, html, selector, delimiter, scope_name, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p>Hello</p>|<p>World</p>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  html = "<div><input type=\"radio\"></div>";
  selector = "div input";
  term_array = eterm_array_init();
  find(w, html, selector, delimiter, scope_name, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<input type=\"radio\"></input>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  html = "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>";
  selector = "*";
  term_array = eterm_array_init();
  find(w, html, selector, delimiter, scope_name, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<html><head></head><body><h1>Hello</h1><p>World</p></body></html>|<head></head>|<body><h1>Hello</h1><p>World</p></body>|<h1>Hello</h1>|<p>World</p>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);


  html = "<p>Hello</p><p>World</p>";
  selector = ":contains(Hello)";
  term_array = eterm_array_init();
  find(w, html, selector, delimiter, scope_name, term_array);
  result = eterm_array_join(term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p>Hello</p>") != 0) {
    eterm_array_destroy(term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(term_array);
  free(result);

  // NOT SUPPORTED RIGHT NOW
  // html = "<p><span id=\"hello\">Hello</span></p><p><span name=\"value\">World</span></p>";
  // selector = "[name!=\"value\"]";
  // result = find(w, html, selector, "|");
  // printf("8: %s\n", result);
  // if(strcmp(result, "<a>some link</a>") != 0){
  //   return 1;
  // }

  html_destroy(w);
  printf("ok\n");
  return 0;
}