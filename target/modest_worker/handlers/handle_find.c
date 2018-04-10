#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char* find(html_workspace_t* w, const char* html, const char* selector, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, "html", selector_index);

  int buffer_index = html_serialize_collection(w, collection_index);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, delimiter);

  return result;
}

ETERM* handle_find(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* find_pattern = erl_format("{find, Html, Selector, Delimiter}");

  if (erl_match(find_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(find_pattern, "Html");
    ETERM* selector_term = erl_var_content(find_pattern, "Selector");
    ETERM* delimiter_term = erl_var_content(find_pattern, "Delimiter");
    
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = find(workspace, html, selector, delimiter);
    ETERM* result_bin = erl_mk_binary(result, strlen(result));
    response = erl_format("{find, ~w}", result_bin);

    // free allocated resources
    html_free(result);
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(delimiter_term);
  }

  erl_free_term(find_pattern);
  return response;
}