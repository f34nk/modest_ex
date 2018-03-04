#include "handlers.h"

#include "modest_find.h"
#include "modest_serialize.h"
#include "modest_attribute.h"
#include "modest_text.h"

#define DEFAULT_FIND_DELIMITER "|"

void
handle_emsg(state_t* state, ErlMessage* emsg)
{
  switch(emsg->type)
  {
    case ERL_REG_SEND:
    case ERL_SEND:
      handle_send(state, emsg);
      break;
    case ERL_LINK:
    case ERL_UNLINK:
      break;
    case ERL_EXIT:
      break;
  }

  // its our responsibility to free these pointers
  erl_free_compound(emsg->msg);
  erl_free_compound(emsg->to);
  erl_free_compound(emsg->from);
}

void
handle_send(state_t* state, ErlMessage* emsg)
{
  ETERM *find_pattern = erl_format("{find, Html, Selector}");
  ETERM *find_pattern_delimiter = erl_format("{find, Html, Selector, Delimiter}");
  ETERM *serialize_pattern = erl_format("{serialize, Html}");
  ETERM *get_attribute_pattern = erl_format("{get_attribute, Html, Key, Delimiter}");
  ETERM *get_selected_attribute_pattern = erl_format("{get_attribute, Html, Selector, Key, Delimiter}");
  ETERM *set_attribute_pattern = erl_format("{set_attribute, Html, Key, Value}");
  ETERM *set_selected_attribute_pattern = erl_format("{set_attribute, Html, Selector, Key, Value}");
  ETERM *get_text_pattern = erl_format("{get_text, Html, Delimiter}");
  ETERM *get_selected_text_pattern = erl_format("{get_text, Html, Selector, Delimiter}");
  ETERM *set_text_pattern = erl_format("{set_text, Html, Text}");
  ETERM *set_selected_text_pattern = erl_format("{set_text, Html, Selector, Text}");
  ETERM *response;

  if (erl_match(find_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(find_pattern, "Html");
    ETERM *selector = erl_var_content(find_pattern, "Selector");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);

    const char* result_string = modest_find(html_string, selector_string, DEFAULT_FIND_DELIMITER);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{find, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
  }
  else if (erl_match(find_pattern_delimiter, emsg->msg))
  {
    ETERM *html = erl_var_content(find_pattern_delimiter, "Html");
    ETERM *selector = erl_var_content(find_pattern_delimiter, "Selector");
    ETERM *delimiter = erl_var_content(find_pattern_delimiter, "Delimiter");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

    const char* result_string = modest_find(html_string, selector_string, delimiter_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{find, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(delimiter);
  }
  else if (erl_match(serialize_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(serialize_pattern, "Html");
    char* html_string = (char*)ERL_BIN_PTR(html);

    const char* result_string = modest_serialize(html_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{serialize, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
  }
  // ATTRIBUTE
  else if (erl_match(get_selected_attribute_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(get_selected_attribute_pattern, "Html");
    ETERM *selector = erl_var_content(get_selected_attribute_pattern, "Selector");
    ETERM *key = erl_var_content(get_selected_attribute_pattern, "Key");
    ETERM *delimiter = erl_var_content(get_selected_attribute_pattern, "Delimiter");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* key_string = (char*)ERL_BIN_PTR(key);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

    const char* result_string = modest_select_and_get_attribute(html_string, selector_string, key_string, delimiter_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{get_attribute, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(key);
    erl_free_term(delimiter);
  }
  else if (erl_match(get_attribute_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(get_attribute_pattern, "Html");
    ETERM *key = erl_var_content(get_attribute_pattern, "Key");
    ETERM *delimiter = erl_var_content(get_attribute_pattern, "Delimiter");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* key_string = (char*)ERL_BIN_PTR(key);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

    const char* result_string = modest_get_attribute(html_string, key_string, delimiter_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{get_attribute, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(key);
    erl_free_term(delimiter);
  }
  else if (erl_match(set_selected_attribute_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(set_selected_attribute_pattern, "Html");
    ETERM *selector = erl_var_content(set_selected_attribute_pattern, "Selector");
    ETERM *key = erl_var_content(set_selected_attribute_pattern, "Key");
    ETERM *value = erl_var_content(set_selected_attribute_pattern, "Value");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* key_string = (char*)ERL_BIN_PTR(key);
    char* value_string = (char*)ERL_BIN_PTR(value);

    const char* result_string = modest_select_and_set_attribute(html_string, selector_string, key_string, value_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{set_attribute, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(key);
    erl_free_term(value);
  }
  else if (erl_match(set_attribute_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(set_attribute_pattern, "Html");
    ETERM *key = erl_var_content(set_attribute_pattern, "Key");
    ETERM *value = erl_var_content(set_attribute_pattern, "Value");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* key_string = (char*)ERL_BIN_PTR(key);
    char* value_string = (char*)ERL_BIN_PTR(value);

    const char* result_string = modest_set_attribute(html_string, key_string, value_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{set_attribute, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(key);
    erl_free_term(value);
  }
  // TEXT
  else if (erl_match(get_selected_text_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(get_selected_text_pattern, "Html");
    ETERM *selector = erl_var_content(get_selected_text_pattern, "Selector");
    ETERM *delimiter = erl_var_content(get_selected_text_pattern, "Delimiter");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

    const char* result_string = modest_select_and_get_text(html_string, selector_string, delimiter_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{get_text, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(delimiter);
  }
  else if (erl_match(get_text_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(get_text_pattern, "Html");
    ETERM *delimiter = erl_var_content(get_text_pattern, "Delimiter");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

    const char* result_string = modest_get_text(html_string, delimiter_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{get_text, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(delimiter);
  }
  else if (erl_match(set_selected_text_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(set_selected_text_pattern, "Html");
    ETERM *selector = erl_var_content(set_selected_text_pattern, "Selector");
    ETERM *text = erl_var_content(set_selected_text_pattern, "Text");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* text_string = (char*)ERL_BIN_PTR(text);

    const char* result_string = modest_select_and_set_text(html_string, selector_string, text_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{set_text, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(text);
  }
  else if (erl_match(set_text_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(set_text_pattern, "Html");
    ETERM *text = erl_var_content(set_text_pattern, "Text");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* text_string = (char*)ERL_BIN_PTR(text);

    const char* result_string = modest_set_text(html_string, text_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{set_text, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(text);
  }
  else
  {
    response = err_term("unknown_call");
    return;
  }

  // send response
  erl_send(state->fd, emsg->from, response);

  // free allocated resources
  erl_free_compound(response);
  erl_free_term(find_pattern);
  erl_free_term(find_pattern_delimiter);
  erl_free_term(serialize_pattern);
  erl_free_term(get_attribute_pattern);
  erl_free_term(get_selected_attribute_pattern);
  erl_free_term(set_attribute_pattern);
  erl_free_term(set_selected_attribute_pattern);
  erl_free_term(get_text_pattern);
  erl_free_term(get_selected_text_pattern);
  erl_free_term(set_text_pattern);
  erl_free_term(set_selected_text_pattern);

  // free the free-list
  erl_eterm_release();

  return;
}