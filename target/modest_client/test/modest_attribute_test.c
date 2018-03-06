
#include "modest_attribute.h"
int main(int argc, const char * argv[])
{
  const char *html = "<a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a>";
  char* result = modest_get_attribute(html, "href", "|");
  printf("%s\n", result);
  if(strcmp(result, "https://elixir-lang.org|https://google.de") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a></p>";
  result = modest_select_and_get_attribute(html, "p a", "href", "|");
  printf("%s\n", result);
  if(strcmp(result, "https://elixir-lang.org|https://google.de") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a href="">Hello</a> World</p>";
  const char *scope = "body_first_child";
  result = modest_select_and_set_attribute(html, "p a", "href", "https://elixir-lang.org", scope);
  printf("%s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a> World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a href="">Hello</a><a href="">World</a></p>";
  result = modest_select_and_set_attribute(html, "p a", "href", "https://elixir-lang.org", scope);
  printf("%s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://elixir-lang.org\">World</a></p>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a>Hello</a> World</p>";
  result = modest_select_and_set_attribute(html, "p a", "href", "https://elixir-lang.org", scope);
  printf("%s\n", result);
  if(strcmp(result, "<p><a href=\"https://elixir-lang.org\">Hello</a> World</p>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}