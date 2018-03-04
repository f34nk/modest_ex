#include "modest_serialize.h"

#include "handle_serialize.h"

ETERM *handle_serialize(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *serialize_pattern = erl_format("{serialize, Html}");
    
    if (erl_match(serialize_pattern, emsg->msg))
    {
      ETERM *html = erl_var_content(serialize_pattern, "Html");
      char* html_string = (char*)ERL_BIN_PTR(html);

      const char* result_string = modest_serialize(html_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{serialize, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
    }

    erl_free_term(serialize_pattern);
  }
  return response;
}