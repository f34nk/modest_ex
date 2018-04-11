#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"
#include "eterm_array.h"

void compare(html_workspace_t* w, const char* html, const char* new_html, const char* scope_name, eterm_array_t* result_array)
{
  const char* selector = "body > *";
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  scope_name = "html";
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  const char* new_selector = selector;
  int new_tree_index = html_parse_tree(w, new_html, strlen(new_html));
  int new_selector_index = html_prepare_selector(w, new_selector, strlen(new_selector));
  const char* new_scope_name = scope_name;
  int new_collection_index  = html_select(w, new_tree_index, new_scope_name, new_selector_index);

  html_vec_int_t buffer_indices;
  html_vec_init(&buffer_indices);
  html_compare(w, collection_index, new_collection_index, &buffer_indices);

  int i; int val;
  html_vec_foreach(&buffer_indices, val, i) {
    int buffer_index = val;
    html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
    char* string = html_vec_join(buffer, "|");
    if(result_array != NULL) {
      eterm_array_push(result_array, erl_mk_binary(string, strlen(string)));
    }
    html_free(string);
  }
  html_vec_deinit(&buffer_indices);
}

ETERM* handle_compare(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{compare, Html1, Html2, Scope}");

  if (erl_match(pattern, emsg->msg))
  {
    ETERM* html1_term = erl_var_content(pattern, "Html1");
    ETERM* html2_term = erl_var_content(pattern, "Html2");
    ETERM* scope_term = erl_var_content(pattern, "Scope");
    char* html1 = (char*)ERL_BIN_PTR(html1_term);
    char* html2 = (char*)ERL_BIN_PTR(html2_term);
    char* scope = (char*)ERL_BIN_PTR(scope_term);

    html_workspace_t* workspace = html_init();
  
    eterm_array_t* result = eterm_array_init();
    compare(workspace, html1, html2, scope, result);

    ETERM* list_term = eterm_array_to_list(result);
    response = erl_format("{compare, ~w}", list_term);
  
    // free allocated resources
    eterm_array_destroy(result);
    erl_free_term(list_term);
    html_destroy(workspace);
    erl_free_term(html1_term);
    erl_free_term(html2_term);
    erl_free_term(scope_term);
  }

  erl_free_term(pattern);
  return response;
}