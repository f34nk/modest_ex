#include "erl_interface.h"
#include "ei.h"

#include "modest_replace.h"

ETERM *handle_replace(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *replace_pattern = erl_format("{replace, Html, Selector, NewHtml}");;
    
    if (erl_match(replace_pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(replace_pattern, "Html");
      ETERM *selector = erl_var_content(replace_pattern, "Selector");
      ETERM *new_html = erl_var_content(replace_pattern, "NewHtml");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);
      char* new_html_string = (char*)ERL_BIN_PTR(new_html);

      const char* result_string = modest_select_and_replace(html_string, selector_string, new_html_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{replace, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
      erl_free_term(new_html);
    }
  
    erl_free_term(replace_pattern);
  }
  return response;
}