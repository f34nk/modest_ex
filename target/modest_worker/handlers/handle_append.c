#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char *select_and_append(html_workspace_t *w, const char *html, const char *selector, const char *new_html, const char *scope_name)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  const char *new_html = "<span>Append</span><span>Me</span>";
  int new_tree_index = html_parse_tree(w, new_html, strlen(new_html));
  const char *new_scope_name = "body_children";
  int new_collection_index  = html_select_scope(w, new_tree_index, new_scope_name);

  html_append_collection(w, collection_index, new_collection_index);

  int buffer_index = html_serialize_collection(w, collection_index);
  html_vec_str_t *buffer = html_get_buffer(w, buffer_index);
  char *result = html_vec_join(buffer, "");

  return result;
}

ETERM *handle_append(ErlMessage* emsg){
  ETERM *response = NULL;
  ETERM *pattern = erl_format("{append, Html, Selector, NewHtml, Scope}");;
  
  if (erl_match(pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(pattern, "Html");
    ETERM *selector = erl_var_content(pattern, "Selector");
    ETERM *new_html = erl_var_content(pattern, "NewHtml");
    ETERM *scope = erl_var_content(pattern, "Scope");

    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* new_html_string = (char*)ERL_BIN_PTR(new_html);
    char* scope_string = (char*)ERL_BIN_PTR(scope);

    html_workspace_t *workspace = html_init();
    char* result_string = select_and_append(workspace, html_string, selector_string, new_html_string, scope_string);

    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{append, ~w}", result_bin);

    // free allocated resources
    html_free(result_string);
    html_destroy(workspace);
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(new_html);
    erl_free_term(scope);
  }
  
  erl_free_term(pattern);
  return response;
}