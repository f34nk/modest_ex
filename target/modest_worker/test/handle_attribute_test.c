
#include "test_includes.h"
int main(int argc, const char * argv[])
{
  html_workspace_t* w = html_init();

  const char *html = "<a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a>";
  char* result = get_attribute(w, html, "href", "|");
  printf("-> %s\n", result);
  if(strcmp(result, "https://elixir-lang.org|https://google.de") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a></p>";
  result = select_and_get_attribute(w, html, "p a", "href", "|");
  printf("-> %s\n", result);
  if(strcmp(result, "https://elixir-lang.org|https://google.de") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<p><a href="">Hello</a> World</p>";
  const char *scope = "body_children";
  result = select_and_set_attribute(w, html, "p a", "href", "https://elixir-lang.org", scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a> World</p>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<p><a href="">Hello</a><a href="">World</a></p>";
  result = select_and_set_attribute(w, html, "p a", "href", "https://elixir-lang.org", scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://elixir-lang.org\">World</a></p>") != 0){
    printf("Failed\n");
    html_free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  html_free(result);

  html = "<p><a>Hello</a> World</p>";
  result = select_and_set_attribute(w, html, "p a", "href", "https://elixir-lang.org", scope);
  printf("-> %s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a> World</p>") != 0){
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