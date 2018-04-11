
#include "test_includes.h"
#include "eterm_array.h"

int main(int argc, const char * argv[])
{
  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  html_workspace_t* w = html_init();

  const char *html1 = "<div>Hello</div>";
  const char *html2 = "<div>Hello<span>World</span></div>";
  const char *scope = "body_children";
  
  eterm_array_t* a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  char *result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<append|html body div(19)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div>Hello<span>World</span></div><div>Other</div>";
  html2 = "<div>Hello</div><div>Other</div>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<remove|html body div(5)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div>Hello</div><div>World</div>";
  html2 = "<div>Hello<span>Other</span></div><div>World</div>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<append|html body div(19)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div>Hello<ul><li>Coffee</li><li>Tea<ul><li>Black tea</li><ul><li>Green tea</li><li>Blue tea</li></ul></ul></li><li>Milk</li></ul></div>";
  html2 = "<div>Hello<ul><li>Coffee</li><li>Tea<ul><li>Black tea</li><ul><li>Green tea</li></ul></ul></li><li>Milk</li></ul></div><span>World</span>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<remove|html body div(15)....>|#Bin<append|html body|<sp(15)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div>Hello</div>";
  html2 = "<div>World</div>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<set_text|html body d(8)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div class=\"first\">Hello</div><div class=\"second\">World</div>";
  html2 = "<div class=\"first\">Hello</div><div class=\"other\">World</div>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<set_attribute|html b(19)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div class=\"other\">Hello</div>";
  html2 = "<div>Hello</div>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<set_attribute|html b(14)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div>Hello</div>";
  html2 = "<div class=\"other\">Hello</div>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<set_attribute|html b(19)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  html1 = "<div>Hello</div>";
  html2 = "<span>World</span>";
  a = eterm_array_init();
  compare(w, html1, html2, scope, a);
  result = eterm_array_join(a, "|");
  printf("-> %s\n", result);
  if(strcmp(result, "#Bin<set_tag|html body di(6)....>|#Bin<set_text|html body s(9)....>") != 0){
    printf("Failed\n");
    eterm_array_destroy(a);
    free(result);
    TEST_ERROR
    return 1;
  }
  eterm_array_destroy(a);
  free(result);

  //?
  //  html1 = "<div>Hello</div>";
  // html2 = "";
  // a = eterm_array_init();
  // compare(w, html1, html2, scope, a);
  // result = eterm_array_join(a, "|");
  // printf("-> %s\n", result);
  // if(strcmp(result, "#Bin<set_text|html body d(8)....>") != 0){
  //   printf("Failed\n");
  //   eterm_array_destroy(a);
  //   free(result);
  //   TEST_ERROR
  //   return 1;
  // }
  // eterm_array_destroy(a);
  // free(result);

  // ?
  // html1 = "";
  // html2 = "<div>Hello</div>";
  // a = eterm_array_init();
  // compare(w, html1, html2, scope, a);
  // result = eterm_array_join(a, "|");
  // printf("-> %s\n", result);
  // if(strcmp(result, "#Bin<set_text|html body d(8)....>") != 0){
  //   printf("Failed\n");
  //   eterm_array_destroy(a);
  //   free(result);
  //   TEST_ERROR
  //   return 1;
  // }
  // eterm_array_destroy(a);
  // free(result);

  html_destroy(w);
  printf("ok\n");
  return 0;
}