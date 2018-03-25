
#include "modest_compare.h"
int main(int argc, const char * argv[])
{
  const char *html1 = "<div>Hello</div>";
  const char *html2 = "<div>Hello<span>World</span></div>";
  const char *scope = "body_children";
  char* result = modest_compare(html1, html2, scope);
  printf("1: %s\n", result);
  if(strcmp(result, "[[\"append\", \"div\", \"<span>World</span>\"]]") != 0){
    printf("Failed\n");
    return 1;
  }
  
  html1 = "<div>Hello<span>World</span></div><div>Other</div>";
  html2 = "<div>Hello</div><div>Other</div>";
  result = modest_compare(html1, html2, scope);
  printf("2: %s\n", result);
  if(strcmp(result, "[[\"remove\", \"div span\"]]") != 0){
    printf("Failed\n");
    return 1;
  }
  
  html1 = "<div>Hello</div><div>World</div>";
  html2 = "<div>Hello<span>Other</span></div><div>World</div>";
  result = modest_compare(html1, html2, scope);
  printf("3: %s\n", result);
  if(strcmp(result, "[[\"append\", \"div\", \"<span>Other</span>\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "<div>Hello<ul><li>Coffee</li><li>Tea<ul><li>Black tea</li><ul><li>Green tea</li><li>Blue tea</li></ul></ul></li><li>Milk</li></ul></div>";
  html2 = "<div>Hello<ul><li>Coffee</li><li>Tea<ul><li>Black tea</li><ul><li>Green tea</li></ul></ul></li><li>Milk</li></ul></div><span>World</span>";
  result = modest_compare(html1, html2, scope);
  printf("4: %s\n", result);
  if(strcmp(result, "[[\"remove\", \"div ul li ul ul li\"], [\"append\", \"body\", \"<span>World</span>\"]]") != 0){
    printf("Failed\n");
    return 1;
  }
  
  html1 = "<div>Hello</div>";
  html2 = "<div>World</div>";
  result = modest_compare(html1, html2, scope);
  printf("5: %s\n", result);
  if(strcmp(result, "[[\"set_text\", \"div\", \"World\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "<div class=\"first\">Hello</div><div class=\"second\">World</div>";
  html2 = "<div class=\"first\">Hello</div><div class=\"other\">World</div>";
  result = modest_compare(html1, html2, scope);
  printf("6: %s\n", result);
  if(strcmp(result, "[[\"set_attribute\", \"div\", \"class\", \"other\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "<div class=\"other\">Hello</div>";
  html2 = "<div>Hello</div>";
  result = modest_compare(html1, html2, scope);
  printf("7: %s\n", result);
  if(strcmp(result, "[[\"set_attribute\", \"div\", \"class\", \"\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "<div>Hello</div>";
  html2 = "<div class=\"other\">Hello</div>";
  result = modest_compare(html1, html2, scope);
  printf("8: %s\n", result);
  if(strcmp(result, "[[\"set_attribute\", \"div\", \"class\", \"other\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "<div>Hello</div>";
  html2 = "<span>World</span>";
  result = modest_compare(html1, html2, scope);
  printf("9: %s\n", result);
  if(strcmp(result, "[[\"set_tag\", \"div\", \"span\"], [\"set_text\", \"span\", \"World\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "<div>Hello</div>";
  html2 = "";
  result = modest_compare(html1, html2, scope);
  printf("10: %s\n", result);
  if(strcmp(result, "[[\"remove\", \"div\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  html1 = "";
  html2 = "<div>Hello</div>";
  result = modest_compare(html1, html2, scope);
  printf("10: %s\n", result);
  if(strcmp(result, "[[\"append\", \"body\", \"<div>Hello</div>\"]]") != 0){
    printf("Failed\n");
    return 1;
  }

  printf("ok\n");
  return 0;
}