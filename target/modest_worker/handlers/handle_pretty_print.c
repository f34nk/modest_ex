#include "erl_interface.h"
#include "ei.h"

#include "modest_pretty_print.h"

ETERM *handle_pretty_print(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *pattern = erl_format("{pretty_print, Html}");
  
  if (erl_match(pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(pattern, "Html");
    char* html_string = (char*)ERL_BIN_PTR(html);

    const char* result_string = modest_pretty_print(html_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{pretty_print, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
  }

  erl_free_term(pattern);
  return response;
}