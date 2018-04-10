#include <stdio.h>
#include <stdlib.h>

#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char* slice_selected(html_workspace_t* w, const char* html, const char* selector, int start, int end, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, "html", selector_index);

  collection_index = html_slice(w, collection_index, start, end);

  // int buffer_index = html_serialize_tree(w, tree_index, scope_name);
  int buffer_index = html_serialize_collection(w, collection_index);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, delimiter);

  return result;
}

ETERM* handle_slice(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{slice, Html, Selector, StartIndex, EndIndex, Delimiter}");

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    ETERM* selector_term = erl_var_content(pattern, "Selector");
    ETERM* start_term = erl_var_content(pattern, "StartIndex");
    ETERM* end_term = erl_var_content(pattern, "EndIndex");
    ETERM* delimiter_term = erl_var_content(pattern, "Delimiter");
    
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* start = (char*)ERL_BIN_PTR(start_term);
    char* end = (char*)ERL_BIN_PTR(end_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = slice_selected(workspace, html, selector, atoi(start), atoi(end), delimiter);
    ETERM* result_bin = erl_mk_binary(result, strlen(result));
    response = erl_format("{slice, ~w}", result_bin);

    // free allocated resources
    html_free(result);
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(start_term);
    erl_free_term(end_term);
    erl_free_term(delimiter_term);
  }

  erl_free_term(pattern);
  return response;
}