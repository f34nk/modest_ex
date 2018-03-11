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

#define MAX_HANDLERS 13
ETERM* (*HANDLERS[MAX_HANDLERS])() = {handle_text, handle_serialize, handle_remove, handle_find, handle_attribute, handle_append, handle_prepend, handle_insert_before, handle_insert_after, handle_replace, handle_slice, handle_position, handle_wrap};

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
  ETERM *response = NULL;

  for(int i = 0; i < MAX_HANDLERS; i++){
    response = HANDLERS[i](emsg, response);
  }

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