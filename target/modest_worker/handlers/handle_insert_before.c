#include "erl_interface.h"
#include "ei.h"

#include "modest_insert_before.h"

ETERM *handle_insert_before(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *pattern = erl_format("{insert_before, Html, Selector, NewHtml, Scope}");;
  
  if (erl_match(pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(pattern, "Html");
    ETERM *selector = erl_var_content(pattern, "Selector");
    ETERM *new_html = erl_var_content(pattern, "NewHtml");
    ETERM *scope = erl_var_content(pattern, "Scope");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* new_html_string = (char*)ERL_BIN_PTR(new_html);
    char* scope_string = (char*)ERL_BIN_PTR(scope);

    const char* result_string = modest_select_and_insert_before(html_string, selector_string, new_html_string, scope_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{insert_before, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(new_html);
    erl_free_term(scope);
  }

  erl_free_term(pattern);
  return response;
}