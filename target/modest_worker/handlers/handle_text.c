#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char* select_and_get_text(html_workspace_t* w, const char* html, const char* selector, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  const char* scope_name = "html";
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int text_index = html_get_text(w, collection_index);

  html_vec_str_t* text = html_get_buffer(w, text_index);
  char* result = html_vec_join(text, delimiter);

  return result;
}

char* get_text(html_workspace_t* w, const char* html, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  const char* selector = "*";
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  const char* scope_name = "html";
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int text_index = html_get_text(w, collection_index);

  html_vec_str_t* text = html_get_buffer(w, text_index);
  char* result = html_vec_join(text, delimiter);

  return result;
}

char* select_and_set_text(html_workspace_t* w, const char* html, const char* selector, const char* text, const char* scope_name)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int text_index = html_set_text(w, collection_index, text);

  int buffer_index = html_serialize_tree(w, tree_index, scope_name);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, "");

  return result;
}

ETERM* handle_text(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* get_text_pattern = erl_format("{get_text, Html, Delimiter}");
  ETERM* get_selected_text_pattern = erl_format("{get_text, Html, Selector, Delimiter}");
  // ETERM *set_text_pattern = erl_format("{set_text, Html, Text}");
  ETERM* set_selected_text_pattern = erl_format("{set_text, Html, Selector, Text, Scope}");

  if (erl_match(get_selected_text_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(get_selected_text_pattern, "Html");
    ETERM* selector_term = erl_var_content(get_selected_text_pattern, "Selector");
    ETERM* delimiter_term = erl_var_content(get_selected_text_pattern, "Delimiter");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = select_and_get_text(workspace, html, selector, delimiter);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{get_text, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to get text"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(delimiter_term);
  }
  else if (erl_match(get_text_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(get_text_pattern, "Html");
    ETERM* delimiter_term = erl_var_content(get_text_pattern, "Delimiter");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = get_text(workspace, html, delimiter);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{get_text, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to get text"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(delimiter_term);
  }
  else if (erl_match(set_selected_text_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(set_selected_text_pattern, "Html");
    ETERM* selector_term = erl_var_content(set_selected_text_pattern, "Selector");
    ETERM* text_term = erl_var_content(set_selected_text_pattern, "Text");
    ETERM* scope_term = erl_var_content(set_selected_text_pattern, "Scope");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* text = (char*)ERL_BIN_PTR(text_term);
    char* scope = (char*)ERL_BIN_PTR(scope_term);

    html_workspace_t* workspace = html_init();
    char* result = select_and_set_text(workspace, html, selector, text, scope);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{set_text, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to set text"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(text_term);
    erl_free_term(scope_term);
  }

  erl_free_term(get_text_pattern);
  erl_free_term(get_selected_text_pattern);
  // erl_free_term(set_text_pattern);
  erl_free_term(set_selected_text_pattern);
  return response;
}