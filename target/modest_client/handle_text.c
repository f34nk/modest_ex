#include "modest_text.h"

#include "handle_text.h"

ETERM *handle_text(ErlMessage* emsg, ETERM *response){
  if(response == NULL){
    ETERM *get_text_pattern = erl_format("{get_text, Html, Delimiter}");
    ETERM *get_selected_text_pattern = erl_format("{get_text, Html, Selector, Delimiter}");
    ETERM *set_text_pattern = erl_format("{set_text, Html, Text}");
    ETERM *set_selected_text_pattern = erl_format("{set_text, Html, Selector, Text}");
    
    if (erl_match(get_selected_text_pattern, emsg->msg))
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

    erl_free_term(get_text_pattern);
    erl_free_term(get_selected_text_pattern);
    erl_free_term(set_text_pattern);
    erl_free_term(set_selected_text_pattern);
  }
  return response;
}