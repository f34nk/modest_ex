#include "erl_interface.h"
#include "ei.h"
#include "eterm_array.h"

#include "modest_html.h"

char* pretty_print(html_workspace_t* w, const char* html)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  
  // int selector_index = html_prepare_selector(w, selector, strlen(selector));
  // const char* scope_name = "body_children";
  // int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  const char* scope_name = "body_children";
  int collection_index  = html_select_scope(w, tree_index, scope_name);

  bool colorize = false;
  char* result = html_pretty_print(w, collection_index, colorize);

  return result;
}

ETERM* handle_pretty_print(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{pretty_print, Html}");

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    char* html = (char*)ERL_BIN_PTR(html_term);

    html_workspace_t* workspace = html_init();
    char* result = pretty_print(workspace, html);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{pretty_print, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to pretty print html"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
  }

  erl_free_term(pattern);
  return response;
}