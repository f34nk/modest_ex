#ifndef HANDLERS_H
#define HANDLERS_H

#include "erl_interface.h"
#include "ei.h"

ETERM *
handle_text(ErlMessage* emsg, ETERM *response);
ETERM *
handle_serialize(ErlMessage* emsg, ETERM *response);
ETERM *
handle_remove(ErlMessage* emsg, ETERM *response);
ETERM *
handle_find(ErlMessage* emsg, ETERM *response);
ETERM *
handle_attribute(ErlMessage* emsg, ETERM *response);
ETERM *
handle_append(ErlMessage* emsg, ETERM *response);
ETERM *
handle_prepend(ErlMessage* emsg, ETERM *response);
ETERM *
handle_insert_before(ErlMessage* emsg, ETERM *response);
ETERM *
handle_insert_after(ErlMessage* emsg, ETERM *response);

typedef struct _state_t {
  int fd;
} state_t;

void
handle_emsg(state_t* state, ErlMessage* emsg);

void
handle_send(state_t* state, ErlMessage* emsg);

#endif