#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char *find(html_workspace_t *w, const char *html, const char *selector, const char *delimiter, const char *scope_name)
{

}

ETERM *handle_find(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *find_pattern = erl_format("{find, Html, Selector, Delimiter, Scope}");
  
  if (erl_match(find_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(find_pattern, "Html");
    ETERM *selector = erl_var_content(find_pattern, "Selector");
    ETERM *delimiter = erl_var_content(find_pattern, "Delimiter");
    ETERM *scope = erl_var_content(find_pattern, "Scope");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);
    char* scope_string = (char*)ERL_BIN_PTR(scope);

    html_workspace_t *workspace = html_init();
    char* result_string = find(workspace, html_string, selector_string, delimiter_string, scope_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{find, ~w}", result_bin);

    // free allocated resources
    html_free(result_string);
    html_destroy(workspace);
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(delimiter);
    erl_free_term(scope);
  }

  erl_free_term(find_pattern);
  return response;
}