#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char* selected_position(html_workspace_t* w, const char* html, const char* selector, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  const char* scope_name = "html";
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);
  int buffer_index = html_position(w, collection_index);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, delimiter);
  return result;
}

ETERM* handle_position(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{position, Html, Selector, Delimiter}");

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    ETERM* selector_term = erl_var_content(pattern, "Selector");
    ETERM* delimiter_term = erl_var_content(pattern, "Delimiter");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = selected_position(workspace, html, selector, delimiter);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{position, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to get position"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(delimiter_term);
  }

  erl_free_term(pattern);
  return response;
}