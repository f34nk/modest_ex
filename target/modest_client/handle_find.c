#include "modest_find.h"

#include "handle_find.h"

#define DEFAULT_FIND_DELIMITER "|"

ETERM *handle_find(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *find_pattern = erl_format("{find, Html, Selector}");
    ETERM *find_pattern_delimiter = erl_format("{find, Html, Selector, Delimiter}");
    
    if (erl_match(find_pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(find_pattern, "Html");
      ETERM *selector = erl_var_content(find_pattern, "Selector");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);

      const char* result_string = modest_find(html_string, selector_string, DEFAULT_FIND_DELIMITER);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{find, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
    }
    else if (erl_match(find_pattern_delimiter, emsg->msg))
    {
      ETERM *html = erl_var_content(find_pattern_delimiter, "Html");
      ETERM *selector = erl_var_content(find_pattern_delimiter, "Selector");
      ETERM *delimiter = erl_var_content(find_pattern_delimiter, "Delimiter");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);
      char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

      const char* result_string = modest_find(html_string, selector_string, delimiter_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{find, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
      erl_free_term(delimiter);
    }

    erl_free_term(find_pattern);
    erl_free_term(find_pattern_delimiter);
  }
  return response;
}