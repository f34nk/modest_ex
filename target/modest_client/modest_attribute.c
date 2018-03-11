/*
 Copyright (C) 2019 Frank Eickhoff
 
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
#include <string.h>

#include <myhtml/myhtml.h>
#include <modest/finder/finder.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

#include "utils.h"

char *get_attributes_by_key(myhtml_collection_t *collection, const char* key, const char* delimiter);
void set_attributes_by_key(myhtml_collection_t *collection, const char* key, const char* value);

char *get_attributes_by_key(myhtml_collection_t *collection, const char* key, const char* delimiter)
{
  FILE *stream;
  char *buf;
  size_t len;
  stream = open_memstream(&buf, &len);

  if(collection && collection->list && collection->length) {

    for(size_t i = 0; i < collection->length; i++) {
      myhtml_tree_node_t *node = collection->list[i];

      if(node) {
        myhtml_tree_attr_t* attr = myhtml_attribute_by_key(node, key, strlen(key));
        if(attr){
          mycore_string_t *value = myhtml_attribute_value_string(attr);
          if(value){
            fprintf(stream, "%.*s", (int)value->length, value->data);
          }
          if(i < collection->length - 1){
            fprintf(stream, delimiter);
          }
        }
      }
    }
  }

  // close the stream, the buffer is allocated and the size is set !
  fclose(stream);
  // printf ("the result is '%s' (%d characters)\n", buf, len);
  // free(buf);
  
  // TODO: This is a leak. Implement proper memory handling.
  return buf;
}

void set_attributes_by_key(myhtml_collection_t *collection, const char* key, const char* value)
{
  if(collection && collection->list && collection->length) {

    for(size_t i = 0; i < collection->length; i++) {
      myhtml_tree_node_t *node = collection->list[i];

      if(node) {
        myhtml_tree_attr_t* attr = myhtml_attribute_by_key(node, key, strlen(key));
        if(attr){
          // remove old attribute
          myhtml_attribute_remove(node, attr);
          // insert new attribute
          myhtml_attribute_add(node, key, strlen(key), value, strlen(value), MyENCODING_UTF_8);
        }
        else {
          // insert new attribute
          myhtml_attribute_add(node, key, strlen(key), value, strlen(value), MyENCODING_UTF_8);
        }
      }
    }
  }
}

/**
 * Get the value of an attribute for the first element in html string
 * @param  html  [a html string]
 * @param  key  [key of the attribute]
 * @return value [value of the attribute]
 */
const char* modest_get_attribute(const char* html, const char* key, const char* delimiter)
{
  // basic init
  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

  // init tree
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  // parse html
  myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

  // parse html
  myhtml_collection_t *collection = NULL;
  collection = myhtml_get_nodes_by_attribute_key(tree, NULL, NULL, key, strlen(key), NULL);

  char *buf = get_attributes_by_key(collection, key, delimiter);
  
  // release resources
  myhtml_collection_destroy(collection);
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);

  // TODO: This is a leak. Implement proper memory handling.
  return buf;
}

/**
 * Get the value of an attribute for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  key     [key of the attribute]
 * @return value    [value of the attribute]
 */
const char* modest_select_and_get_attribute(const char* html, const char* selector, const char* key, const char* delimiter)
{
  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree = parse_html(html, strlen(html));

  /* create css parser and finder for selectors */
  mycss_entry_t *css_entry = create_css_parser();
  modest_finder_t *finder = modest_finder_create_simple();

  /* parse selectors */
  mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));

  /* find nodes by selector */
  myhtml_collection_t *collection = NULL;
  modest_finder_by_selectors_list(finder, tree->node_html, selectors_list, &collection);

  char *buf = get_attributes_by_key(collection, key, delimiter);

  /* destroy all */
  myhtml_collection_destroy(collection);

  /* destroy selector list */
  mycss_selectors_list_destroy(mycss_entry_selectors(css_entry), selectors_list, true);

  /* destroy Modest Finder */
  modest_finder_destroy(finder, true);

  /* destroy MyCSS */
  mycss_t *mycss = css_entry->mycss;
  mycss_entry_destroy(css_entry, true);
  mycss_destroy(mycss, true);

  /* destroy MyHTML */
  myhtml_t* myhtml = tree->myhtml;
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);

  // TODO: This is a leak. Implement proper memory handling.
  return buf;
}

/**
 * Set the value of an attribute for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  key     [key of the attribute]
 * @param  value    [value of the attribute]
 * @return          [updated html string]
 */
const char* modest_select_and_set_attribute(const char* html, const char* selector, const char* key, const char* value, const char* scope)
{
  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree = parse_html(html, strlen(html));

  /* create css parser and finder for selectors */
  mycss_entry_t *css_entry = create_css_parser();
  modest_finder_t *finder = modest_finder_create_simple();

  /* parse selectors */
  mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));

  /* find nodes by selector */
  myhtml_collection_t *collection = NULL;
  modest_finder_by_selectors_list(finder, tree->node_html/*get_scope_node(tree, scope)*/, selectors_list, &collection);

  if(collection == NULL || collection->length == 0) {
    printf("missing collection\n");
  }

  set_attributes_by_key(collection, key, value);

  FILE *stream;
  char *buf;
  size_t len;
  stream = open_memstream(&buf, &len);

  // serialize complete html page
  myhtml_serialization_tree_callback(get_scope_node(tree, scope), write_output, stream);
  
  // const char* delimiter = "|";
  // print_found_result(tree, collection, delimiter, stream);

  // close the stream, the buffer is allocated and the size is set !
  fclose(stream);
  // printf ("the result is '%s' (%d characters)\n", buf, len);
  // free(buf);
  
  /* destroy all */
  myhtml_collection_destroy(collection);

  /* destroy selector list */
  mycss_selectors_list_destroy(mycss_entry_selectors(css_entry), selectors_list, true);

  /* destroy Modest Finder */
  modest_finder_destroy(finder, true);

  /* destroy MyCSS */
  mycss_t *mycss = css_entry->mycss;
  mycss_entry_destroy(css_entry, true);
  mycss_destroy(mycss, true);

  /* destroy MyHTML */
  myhtml_t* myhtml = tree->myhtml;
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);

  // TODO: This is a leak. Implement proper memory handling.
  return get_scoped_html(buf, scope);
}