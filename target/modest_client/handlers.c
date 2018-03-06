#include "handlers.h"

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

  response = handle_find(emsg, response);
  response = handle_serialize(emsg, response);
  response = handle_attribute(emsg, response);
  response = handle_text(emsg, response);
  response = handle_remove(emsg, response);
  response = handle_append(emsg, response);
  response = handle_prepend(emsg, response);
  response = handle_insert_before(emsg, response);
  response = handle_insert_after(emsg, response);

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