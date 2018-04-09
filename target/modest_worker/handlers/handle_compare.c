#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char *compare(html_workspace_t *w, const char *html1, const char *html2, const char *scope_name)
{

}

ETERM *handle_compare(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *pattern = erl_format("{compare, Html1, Html2, Scope}");
  
  if (erl_match(pattern, emsg->msg))
  {
    ETERM *html1 = erl_var_content(pattern, "Html1");
    ETERM *html2 = erl_var_content(pattern, "Html2");
    ETERM *scope = erl_var_content(pattern, "Scope");
    char* html1_string = (char*)ERL_BIN_PTR(html1);
    char* html2_string = (char*)ERL_BIN_PTR(html2);
    char* scope_string = (char*)ERL_BIN_PTR(scope);

    html_workspace_t *workspace = html_init();
    char* result_string = compare(workspace, html1_string, html2_string, scope_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{compare, ~w}", result_bin);

    // free allocated resources
    html_free(result_string);
    html_destroy(workspace);
    erl_free_term(html1);
    erl_free_term(html2);
    erl_free_term(scope);
  }

  erl_free_term(pattern);
  return response;
}