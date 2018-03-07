#include <stdio.h>
#include <stdlib.h>

#include "erl_interface.h"
#include "ei.h"

#include "modest_slice.h"

ETERM *handle_slice(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *pattern = erl_format("{slice, Html, Selector, StartIndex, EndIndex, Delimiter, Scope}");
    
    if (erl_match(pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(pattern, "Html");
      ETERM *selector = erl_var_content(pattern, "Selector");
      ETERM *start = erl_var_content(pattern, "StartIndex");
      ETERM *end = erl_var_content(pattern, "EndIndex");
      ETERM *delimiter = erl_var_content(pattern, "Delimiter");
      ETERM *scope = erl_var_content(pattern, "Scope");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);
      char* start_string = (char*)ERL_BIN_PTR(start);
      char* end_string = (char*)ERL_BIN_PTR(end);
      char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);
      char* scope_string = (char*)ERL_BIN_PTR(scope);

      const char* result_string = modest_slice_selected(html_string, selector_string, atoi(start_string), atoi(end_string), delimiter_string, scope_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{slice, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
      erl_free_term(start);
      erl_free_term(end);
      erl_free_term(delimiter);
      erl_free_term(scope);
    }

    erl_free_term(pattern);
  }
  return response;
}