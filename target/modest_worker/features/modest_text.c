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
#include <string.h>

#include <myhtml/myhtml.h>
#include <modest/finder/finder.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

#include "utils.h"

char *get_text(myhtml_collection_t *collection, const char* delimiter);
void set_text(myhtml_tree_t* tree, myhtml_collection_t *collection, const char* text);

char *get_text(myhtml_collection_t *collection, const char* delimiter)
{
  FILE *stream;
  char *buf;
  size_t len;
  stream = open_memstream(&buf, &len);

  if(collection && collection->list && collection->length) {
    for(size_t i = 0; i < collection->length; i++) {
      myhtml_tree_node_t *node = collection->list[i];
      if(node) {
        myhtml_tree_node_t *text_node = myhtml_node_child(node);
        if(text_node) {
          const char* text = myhtml_node_text(text_node, NULL);
          if(text){
            fprintf(stream, "%.*s", (int)strlen(text), text);
            if(i < collection->length - 1){
              fprintf(stream, delimiter);
            }
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

void set_text(myhtml_tree_t* tree, myhtml_collection_t *collection, const char* text)
{
  if(collection && collection->list && collection->length) {

    for(size_t i = 0; i < collection->length; i++) {
      myhtml_tree_node_t *node = collection->list[i];

      if(node) {
        myhtml_tree_node_t *text_node = myhtml_node_child(node);
        if(text_node) {
          myhtml_node_delete(text_node);
        }
        myhtml_tree_node_t* new_text_node = myhtml_node_create(tree, MyHTML_TAG__TEXT, MyHTML_NAMESPACE_HTML);
        mycore_string_t *string = myhtml_node_text_set(new_text_node, text, strlen(text), MyENCODING_UTF_8);
        
        myhtml_node_append_child(node, new_text_node);
      }
    }
  }
  return tree;
}

/**
 * Get the text for the first element in html string
 * @param  html  [a html string]
 * @param  delimiter  [string]
 * @return value [the text]
 */
const char* modest_get_text(const char* html, const char* delimiter)
{
  // basic init
  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

  // init tree
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  // parse html
  myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

  const char* selector = "body *";

  /* create css parser and finder for selectors */
  mycss_entry_t *css_entry = create_css_parser();
  modest_finder_t *finder = modest_finder_create_simple();

  /* parse selectors */
  mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));

  /* find nodes by selector */
  myhtml_collection_t *collection = NULL;
  modest_finder_by_selectors_list(finder, tree->node_html, selectors_list, &collection);

  char *buf = get_text(collection, delimiter);
  
  // release resources
  myhtml_collection_destroy(collection);
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);

  // TODO: This is a leak. Implement proper memory handling.
  return buf;
}

/**
 * Get the text for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  delimiter  [string]
 * @return value    [the text]
 */
const char* modest_select_and_get_text(const char* html, const char* selector, const char* delimiter)
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

  char *buf = get_text(collection, delimiter);

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
 * Set text for the selected element in html string
 * @param  html     [a html string]
 * @param  selector [a CSS selector]
 * @param  text     [the text]
 * @return          [updated html string]
 */
const char* modest_select_and_set_text(const char* html, const char* selector, const char* text, const char* scope)
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
    // printf("missing collection\n");
  }

  set_text(tree, collection, text);

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