
#include "test_includes.h"
int main(int argc, const char* argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  html_workspace_t* w = html_init();

  const char* html = "<a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a>";
  vec_eterm_t term_array; 
  eterm_vec_init(&term_array);
  get_attribute(w, html, "href", "|", &term_array);
  char* result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "https://elixir-lang.org|https://google.de") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html = "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a></p>";
  eterm_vec_init(&term_array);
  select_and_get_attribute(w, html, "p a", "href", "|", &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "https://elixir-lang.org|https://google.de") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html = "<p><a href="">Hello</a> World</p>";
  const char* scope_name = "body_children";
  eterm_vec_init(&term_array);
  select_and_set_attribute(w, html, "p a", "href", "https://elixir-lang.org", scope_name, &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a> World</p>") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html = "<p><a href="">Hello</a><a href="">World</a></p>";
  eterm_vec_init(&term_array);
  select_and_set_attribute(w, html, "p a", "href", "https://elixir-lang.org", scope_name, &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://elixir-lang.org\">World</a></p>") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html = "<p><a>Hello</a> World</p>";
  eterm_vec_init(&term_array);
  select_and_set_attribute(w, html, "p a", "href", "https://elixir-lang.org", scope_name, &term_array);
  result = eterm_vec_join(&term_array, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a> World</p>") != 0) {
    eterm_vec_destroy(&term_array);
    free(result);
    html_destroy(w);
    TEST_ERROR
    return 1;
  }
  eterm_vec_destroy(&term_array);
  free(result);

  html_destroy(w);
  printf("ok\n");
  return 0;
}