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

#include <stdio.h>
#include <stdlib.h>

// #include <myhtml/api.h>
#include <myhtml/myhtml.h>
#include <modest/finder/finder.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

#include "utils.h"

/**
 * Serialize any string with valid or broken html.
 * @param  html [a html string]
 * @return      [a html string]
 */
const char* modest_serialize(const char* html, const char* scope){
  // basic init
  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

  // init tree
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  // parse html
  myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

  mycore_string_raw_t str_raw;
  mycore_string_raw_clean_all(&str_raw);

  if(myhtml_serialization_tree_buffer(get_scope_node(tree, scope), &str_raw)) {
    fprintf(stderr, "Could not serialization for the tree\n");
    return "";
  }
  // if(myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str_raw)) {
  //   fprintf(stderr, "Could not serialization for the tree\n");
  //   return "";
  // }

  // printf("%s", str_raw.data);
  // mycore_string_raw_destroy(&str_raw, false);

  // release resources
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);

  // TODO: This is a leak. Implement proper memory handling.
  // return str_raw.data;
  return get_scoped_html(str_raw.data, scope);
}