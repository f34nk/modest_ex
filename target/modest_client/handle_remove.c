#include "erl_interface.h"
#include "ei.h"

#include "modest_remove.h"

ETERM *handle_remove(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *remove_pattern = erl_format("{remove, Html, Selector}");
    
    if (erl_match(remove_pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(remove_pattern, "Html");
      ETERM *selector = erl_var_content(remove_pattern, "Selector");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);

      const char* result_string = modest_select_and_remove(html_string, selector_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{remove, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
    }

    erl_free_term(remove_pattern);
  }
  return response;
}