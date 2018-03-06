#include "erl_interface.h"
#include "ei.h"

#include "modest_serialize.h"

ETERM *handle_serialize(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *pattern = erl_format("{serialize, Html, Scope}");
    
    if (erl_match(pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(pattern, "Html");
      ETERM *scope = erl_var_content(pattern, "Scope");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* scope_string = (char*)ERL_BIN_PTR(scope);

      const char* result_string = modest_serialize(html_string, scope_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{serialize, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
    }

    erl_free_term(pattern);
  }
  return response;
}