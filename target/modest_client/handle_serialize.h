#ifndef HANDLE_SERIALIZE_H
#define HANDLE_SERIALIZE_H

#include "erl_interface.h"
#include "ei.h"

ETERM *
handle_serialize(ErlMessage* emsg, ETERM *response);

#endif