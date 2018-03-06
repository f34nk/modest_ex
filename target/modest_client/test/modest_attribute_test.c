
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


  html = "<a href="">Hello</a><a href="">World</a>";
  result = modest_set_attribute(html, "href", "https://elixir-lang.org");
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://elixir-lang.org\">World</a></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<a href="">Hello</a>";
  result = modest_set_attribute(html, "href", "https://elixir-lang.org");
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a href="">Hello</a> World</p>";
  result = modest_select_and_set_attribute(html, "p a", "href", "https://elixir-lang.org");
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><p><a href=\"https://elixir-lang.org\">Hello</a> World</p></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a href="">Hello</a><a href="">World</a></p>";
  result = modest_select_and_set_attribute(html, "p a", "href", "https://elixir-lang.org");
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://elixir-lang.org\">World</a></p></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<a>Hello</a>";
  result = modest_set_attribute(html, "href", "https://elixir-lang.org");
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  html = "<p><a>Hello</a> World</p>";
  result = modest_select_and_set_attribute(html, "p a", "href", "https://elixir-lang.org");
  printf("%s\n", result);
  if(strcmp(result, "<-undef><html><head></head><body><p><a href=\"https://elixir-lang.org\">Hello</a> World</p></body></html>") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}