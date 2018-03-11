#include "erl_interface.h"
#include "ei.h"

#include "modest_remove.h"

ETERM *handle_remove(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *pattern = erl_format("{remove, Html, Selector, Scope}");
  
  if (erl_match(pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(pattern, "Html");
    ETERM *selector = erl_var_content(pattern, "Selector");
    ETERM *scope = erl_var_content(pattern, "Scope");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* scope_string = (char*)ERL_BIN_PTR(scope);

    const char* result_string = modest_select_and_remove(html_string, selector_string, scope_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{remove, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(scope);
  }

  erl_free_term(pattern);
  return response;
}