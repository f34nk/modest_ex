#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char *pretty_print(html_workspace_t *w, const char *html)
{

}

ETERM *handle_pretty_print(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *pattern = erl_format("{pretty_print, Html}");
  
  if (erl_match(pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(pattern, "Html");
    char* html_string = (char*)ERL_BIN_PTR(html);

    html_workspace_t *workspace = html_init();
    char* result_string = pretty_print(workspace, html_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{pretty_print, ~w}", result_bin);

    // free allocated resources
    html_free(result_string);
    html_destroy(workspace);
    erl_free_term(html);
  }

  erl_free_term(pattern);
  return response;
}