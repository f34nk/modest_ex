#include "handlers.h"

// #include "modest_find.h"
// #include "modest_serialize.h"
// #include "modest_attribute.h"
// #include "modest_text.h"

#include "handle_find.h"
#include "handle_serialize.h"
#include "handle_attribute.h"
#include "handle_text.h"

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