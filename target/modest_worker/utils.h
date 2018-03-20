#ifndef UTILS_H
#define UTILS_H

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

#include <myhtml/myhtml.h>

// mystatus_t serialization_bad_selectors(const char* buffer, size_t size, void* ctx);

/**
 * Parse html string into a tree structure.
 * @param  data      [a html string]
 * @param  data_size [size of the html string]
 * @return           [a html tree]
 */
myhtml_tree_t * parse_html(const char* data, size_t data_size);

mycss_entry_t * create_css_parser(void);
mycss_selectors_list_t * prepare_selector(mycss_entry_t *css_entry, const char* selector, size_t selector_size);
void print_found_result(myhtml_tree_t* html_tree, myhtml_collection_t *collection, const char* delimiter, FILE *stream);

char* serialize_node(myhtml_tree_node_t* node);
char* serialize_selector(myhtml_tree_node_t* node);

mystatus_t write_output(const char* data, size_t len, void* ctx);
myhtml_tree_node_t *get_root_node(myhtml_t *myhtml, const char* new_html);

// concat str1 and str2
char *concat_string( const char *str1, const char *str2 );
void remove_substring(char *string, const char *substring);
char** split_string(char* string, const char delimiter);

/**
 * [get_scope_node description]
 * @param  tree  [html tree]
 * @param  scope [can be "html", "head", "body", "body_children", "form"]
 * @return       [description]
 */
myhtml_tree_node_t *get_scope_node(myhtml_tree_t* tree, const char* scope);
const char* get_scoped_selector(const char* selector, const char* scope);


#endif