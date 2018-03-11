#ifndef HANDLE_SEND_H
#define HANDLE_SEND_H

#include <stdio.h>
#include "erl_interface.h"
#include "ei.h"

typedef struct _state_t {
  int fd;
} state_t;

void
handle_emsg(state_t* state, ErlMessage* emsg);

void
handle_send(state_t* state, ErlMessage* emsg);

#endif