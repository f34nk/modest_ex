#ifndef ETERM_ARRAY_H
#define ETERM_ARRAY_H

/*
 Copyright (C) 2018 Frank Eickhoff
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "erl_interface.h"
#include "ei.h"

struct eterm_array
{
  ETERM** data;
  int size;
}
typedef eterm_array_t;

eterm_array_t* eterm_array_init();
bool eterm_array_push(eterm_array_t* array, ETERM* eterm);
bool eterm_array_copy(eterm_array_t* array, const ETERM** data, int length);
void eterm_array_destroy(eterm_array_t* array);
void eterm_array_dump(eterm_array_t* array, FILE* stream);
#define eterm_array_to_list(a) erl_mk_list(a->data, a->size)
char* eterm_array_join(eterm_array_t* array, const char* delimiter);

#endif