#include "erl_interface.h"
#include "ei.h"
#include "eterm_vec.h"

#include "modest_html.h"

void serialize(html_workspace_t* w, const char* html, const char* scope_name, vec_eterm_t* term_array)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int collection_index  = html_select_scope(w, tree_index, scope_name);

  int buffer_index = html_serialize_collection(w, collection_index);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  // char* result = html_vec_join(buffer, "");
  // if(term_array != NULL) {
  //   eterm_array_push(term_array, erl_mk_binary(result, strlen(result)));
  // }
  // html_free(result);
  int i; char* val;
  html_vec_foreach(buffer, val, i) {
    eterm_vec_push(term_array, erl_mk_binary(val, strlen(val)));
  }
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
    vec_eterm_t term_array;
    eterm_vec_init(&term_array);
    serialize(workspace, html, scope, &term_array);
    ETERM* term_list = eterm_vec_to_list(term_array);
    response = erl_format("{serialize, ~w}", term_list);

    // free allocated resources
    eterm_vec_destroy(&term_array);
    erl_free_term(term_list);
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(scope_term);
  }

  erl_free_term(pattern);
  return response;
}