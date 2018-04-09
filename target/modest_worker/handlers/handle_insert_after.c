#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char* select_and_insert_after(html_workspace_t* w, const char* html, const char* selector, const char* new_html, const char* scope_name)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int new_tree_index = html_parse_tree(w, new_html, strlen(new_html));
  const char* new_scope_name = scope_name;
  int new_collection_index  = html_select_scope(w, new_tree_index, new_scope_name);

  html_insert_after(w, collection_index, new_collection_index);

  int buffer_index = html_serialize_collection(w, collection_index);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, "");

  return result;
}

ETERM* handle_insert_after(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{insert_after, Html, Selector, NewHtml, Scope}");;

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    ETERM* selector_term = erl_var_content(pattern, "Selector");
    ETERM* new_html_term = erl_var_content(pattern, "NewHtml");
    ETERM* scope_term = erl_var_content(pattern, "Scope");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* new_html = (char*)ERL_BIN_PTR(new_html_term);
    char* scope = (char*)ERL_BIN_PTR(scope_term);

    html_workspace_t* workspace = html_init();
    char* result = select_and_insert_after(workspace, html, selector, new_html, scope);
    ETERM* result_bin = erl_mk_binary(result, strlen(result));
    response = erl_format("{insert_after, ~w}", result_bin);

    // free allocated resources
    html_free(result);
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(new_html_term);
    erl_free_term(scope_term);
  }

  erl_free_term(pattern);
  return response;
}