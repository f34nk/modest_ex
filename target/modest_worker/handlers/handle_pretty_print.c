#include "erl_interface.h"
#include "ei.h"
#include "eterm_vec.h"

#include "modest_html.h"

void pretty_print(html_workspace_t* w, const char* html, vec_eterm_t* term_array)
{
  int tree_index = html_parse_tree(w, html, strlen(html));

  const char* scope_name = "body_children";
  int collection_index  = html_select_scope(w, tree_index, scope_name);

  bool colorize = false;
  char* result = html_pretty_print(w, collection_index, colorize);
  if(term_array != NULL) {
    eterm_vec_push(term_array, erl_mk_binary(result, strlen(result)));
  }
  html_free(result);
}

ETERM* handle_pretty_print(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{pretty_print, Html}");

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    char* html = (char*)ERL_BIN_PTR(html_term);

    html_workspace_t* workspace = html_init();
    vec_eterm_t term_array;
    eterm_vec_init(&term_array);
    pretty_print(workspace, html, &term_array);
    ETERM* term_list = eterm_vec_to_list(term_array);
    response = erl_format("{pretty_print, ~w}", term_list);

    // free allocated resources
    eterm_vec_destroy(&term_array);
    erl_free_term(term_list);
    html_destroy(workspace);
    erl_free_term(html_term);
  }

  erl_free_term(pattern);
  return response;
}