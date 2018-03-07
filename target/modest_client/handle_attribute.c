#include "erl_interface.h"
#include "ei.h"

#include "modest_attribute.h"

ETERM *handle_attribute(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *get_attribute_pattern = erl_format("{get_attribute, Html, Key, Delimiter}");
    ETERM *get_selected_attribute_pattern = erl_format("{get_attribute, Html, Selector, Key, Delimiter}");
    // ETERM *set_attribute_pattern = erl_format("{set_attribute, Html, Key, Value}");
    ETERM *set_selected_attribute_pattern = erl_format("{set_attribute, Html, Selector, Key, Value, Scope}");
    
    if (erl_match(get_selected_attribute_pattern, emsg->msg))
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
      ETERM *scope = erl_var_content(set_selected_attribute_pattern, "Scope");
      char* html_string = (char*)ERL_BIN_PTR(html);
      char* selector_string = (char*)ERL_BIN_PTR(selector);
      char* key_string = (char*)ERL_BIN_PTR(key);
      char* value_string = (char*)ERL_BIN_PTR(value);
      char* scope_string = (char*)ERL_BIN_PTR(scope);

      const char* result_string = modest_select_and_set_attribute(html_string, selector_string, key_string, value_string, scope_string);
      ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
      response = erl_format("{set_attribute, ~w}", result_bin);

      // free allocated resources
      erl_free_term(html);
      erl_free_term(selector);
      erl_free_term(key);
      erl_free_term(value);
      erl_free_term(scope);
    }
    // else if (erl_match(set_attribute_pattern, emsg->msg))
    // {
    //   ETERM *html = erl_var_content(set_attribute_pattern, "Html");
    //   ETERM *key = erl_var_content(set_attribute_pattern, "Key");
    //   ETERM *value = erl_var_content(set_attribute_pattern, "Value");
    //   char* html_string = (char*)ERL_BIN_PTR(html);
    //   char* key_string = (char*)ERL_BIN_PTR(key);
    //   char* value_string = (char*)ERL_BIN_PTR(value);

    //   const char* result_string = modest_set_attribute(html_string, key_string, value_string);
    //   ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    //   response = erl_format("{set_attribute, ~w}", result_bin);

    //   // free allocated resources
    //   erl_free_term(html);
    //   erl_free_term(key);
    //   erl_free_term(value);
    // }

    erl_free_term(get_attribute_pattern);
    erl_free_term(get_selected_attribute_pattern);
    // erl_free_term(set_attribute_pattern);
    erl_free_term(set_selected_attribute_pattern);
  }
  return response;
}