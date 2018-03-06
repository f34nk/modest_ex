#include "erl_interface.h"
#include "ei.h"

#include "modest_insert_after.h"

ETERM *handle_insert_after(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *append_pattern = erl_format("{insert_after, Html, Selector, NewHtml}");;
    
    if (erl_match(append_pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(append_pattern, "Html");
      ETERM *selector = erl_var_content(append_pattern, "Selector");
      ETERM *new_html = erl_var_content(append_pattern, "NewHtml");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);
      char* new_html_string = (char*)ERL_BIN_PTR(new_html);

      const char* result_string = modest_select_and_insert_after(html_string, selector_string, new_html_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{insert_after, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
      erl_free_term(new_html);
    }
  
    erl_free_term(append_pattern);
  }
  return response;
}