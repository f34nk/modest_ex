#include "erl_interface.h"
#include "ei.h"
#include "eterm_array.h"

#include "modest_html.h"

char* serialize(html_workspace_t* w, const char* html, const char* scope_name)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int collection_index  = html_select_scope(w, tree_index, scope_name);

  int buffer_index = html_serialize_collection(w, collection_index);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, "");

  return result;
}

ETERM* handle_serialize(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{serialize, Html, Scope}");

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    ETERM* scope_term = erl_var_content(pattern, "Scope");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* scope = (char*)ERL_BIN_PTR(scope_term);

    html_workspace_t* workspace = html_init();
    char* result = serialize(workspace, html, scope);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{serialize, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to serialize node"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(scope_term);
  }

  erl_free_term(pattern);
  return response;
}