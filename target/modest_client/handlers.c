#include "handlers.h"

ETERM* handle_text(ErlMessage* emsg, ETERM* response);
ETERM* handle_serialize(ErlMessage* emsg, ETERM* response);
ETERM* handle_remove(ErlMessage* emsg, ETERM* response);
ETERM* handle_find(ErlMessage* emsg, ETERM* response);
ETERM* handle_attribute(ErlMessage* emsg, ETERM* response);
ETERM* handle_append(ErlMessage* emsg, ETERM* response);
ETERM* handle_prepend(ErlMessage* emsg, ETERM* response);
ETERM* handle_insert_before(ErlMessage* emsg, ETERM* response);
ETERM* handle_insert_after(ErlMessage* emsg, ETERM* response);
ETERM* handle_replace(ErlMessage* emsg, ETERM* response);
ETERM* handle_slice(ErlMessage* emsg, ETERM* response);
ETERM* handle_position(ErlMessage* emsg, ETERM* response);
ETERM* handle_wrap(ErlMessage* emsg, ETERM* response);

// ETERM* handle_test(ErlMessage* emsg, ETERM* response)
// {
//   printf("handle_test\n");
//   const char *result_string = "Hello";
//   ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
//   // response = erl_format("{test, ~w}", result_bin);
//   return response;
// }

// ETERM* handle_test(ErlMessage* emsg, ETERM* response);
// ETERM *handle_text(ErlMessage* emsg, ETERM *response);
typedef (*Fi)(ErlMessage* emsg, ETERM* response);
// typedef Fi (*ETERM)(ErlMessage* emsg, ETERM* response);

// typedef struct{
//   ErlMessage* emsg;
//   ETERM* response;
// }handler_t;
// typedef int (*Fi)(handler_t*);
// typedef (*Fi)(ErlMessage* emsg, ETERM* response);

int max_handlers = 1;
// Fi handlers[] = {handle_test};
// Fi handlers[] = {handle_text};
// int max_handlers = 12;
Fi handlers[] = {handle_text, handle_serialize, handle_remove, handle_find, handle_attribute, handle_append, handle_prepend, handle_insert_before, handle_insert_after, handle_replace, handle_slice, handle_position, handle_wrap};

ETERM*
handle_all(ErlMessage* emsg, ETERM* response){
  int max_handlers = sizeof(handlers)/sizeof(handlers[0]);
  // printf("max_handlers %d\n", max_handlers);
  for(int i = 0; i < max_handlers; i++){
    // printf("handle %d\n", i);
    response = handlers[i](emsg, response);
    // printf("next...\n");
  }
  return response;
}

ETERM*
err_term(const char* error_atom)
{
  return erl_format("{error, ~w}", erl_mk_atom(error_atom));
}

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
  ETERM *response;

  response = handle_all(emsg, response);
  
  // response = handle_find(emsg, response);
  // response = handle_serialize(emsg, response);
  // response = handle_attribute(emsg, response);
  // response = handle_text(emsg, response);
  // response = handle_remove(emsg, response);
  // response = handle_append(emsg, response);
  // response = handle_prepend(emsg, response);
  // response = handle_insert_before(emsg, response);
  // response = handle_insert_after(emsg, response);
  // response = handle_replace(emsg, response);
  // response = handle_slice(emsg, response);
  // response = handle_position(emsg, response);
  // response = handle_wrap(emsg, response);

  if(response == NULL)
  {
    response = err_term("unknown_call");
    return;
  }

  // send response
  erl_send(state->fd, emsg->from, response);

  // free allocated resources
  erl_free_compound(response);

  // free the free-list
  erl_eterm_release();

  return;
}