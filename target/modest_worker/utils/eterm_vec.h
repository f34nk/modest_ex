#ifndef ETERM_VEC_H
#define ETERM_VEC_H

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

#include "vec.h"

/**
 * Vector of erlang terms.
 */
typedef vec_t(ETERM*) vec_eterm_t;

#define eterm_vec_foreach(v, var, iter) vec_foreach(v, var, iter)
#define eterm_vec_push(v, val) vec_push(v, val)
#define eterm_vec_reverse(v) vec_reverse(v)
#define eterm_vec_sort(v, fn) vec_sort(v, fn)
#define eterm_vec_pop(v) vec_pop(v)
#define eterm_vec_get(v, i) (v.length > i) ? v.data[i] : -1
#define eterm_vec_init(v) vec_init(v)
#define eterm_vec_clear(v) vec_clear(v)
#define eterm_vec_deinit(v) vec_deinit(v)

#define eterm_vec_to_list(v) erl_mk_list(v.data, v.length)
char* eterm_vec_join(vec_eterm_t* vec, const char* delimiter);
void eterm_vec_dump(vec_eterm_t* v, FILE* stream);
void eterm_vec_destroy(vec_eterm_t* vec);

void eterm_dump(ETERM* term, FILE* stream);
char* eterm_to_string(ETERM* term);

#endif