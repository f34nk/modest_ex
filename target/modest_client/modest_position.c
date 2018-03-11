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
#include "modest_slice.h"

bool compare_position(myhtml_tree_node_t *node, myhtml_tree_node_t *another_node){
  // myhtml_position_t myhtml_node_raw_position();
  myhtml_position_t a = myhtml_node_element_position(node);
  myhtml_position_t b = myhtml_node_element_position(another_node);
  if(a.begin == b.begin) {
    return true;
  }
  return false;
}

void collect_positions(myhtml_collection_t *collection, const char* delimiter, FILE *stream)
{
  if(collection && collection->list && collection->length){
    for(size_t i = 0; i < collection->length; i++) {
      myhtml_tree_node_t *target_node = collection->list[i];
      if(target_node){
        myhtml_tree_node_t* parent = myhtml_node_parent(target_node);
        if(parent){
          int position = -1;
          myhtml_tree_node_t *next = myhtml_node_child(parent);
          while(next && compare_position(target_node, next) == false) {
            next = myhtml_node_next(next);
            if(next){
              if(position == -1) {
                position = 1;
              }
              position += 1;
            }
          }
          fprintf(stream, "%d", position);
          if(i < collection->length - 1){
            fprintf(stream, delimiter);
          }
        }
      }
    }
  }
}

/**
 * Get position of selected child in relation to its parent.
 * @param  html      [a html string]
 * @param  selector  [a CSS selector]
 * @param  delimiter [a delimiter string]
 * @return           [position string]
 */
const char* modest_selected_position(const char* html, const char* selector, const char* delimiter)
{
  // const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  // const char *selector = "div > :nth-child(2n+1):not(:has(a))";

  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree = parse_html(html, strlen(html));

  /* create css parser and finder for selectors */
  mycss_entry_t *css_entry = create_css_parser();
  modest_finder_t *finder = modest_finder_create_simple();

  // const char* new_selector = get_scoped_selector(selector, scope);
  // printf("scoped_selector: %s\n", new_selector);

  /* parse selectors */
  mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));

  /* find nodes by selector */
  myhtml_collection_t *collection = NULL;
  // modest_finder_by_selectors_list(finder, get_scope_node(tree, scope), selectors_list, &collection);
  modest_finder_by_selectors_list(finder, tree->node_html, selectors_list, &collection);

  FILE *stream;
  char *buf;
  size_t len;
  stream = open_memstream(&buf, &len);

  // myhtml_collection_t *new_collection = slice(tree->myhtml, collection, start, end);

  collect_positions(collection, delimiter, stream);

  // close the stream, the buffer is allocated and the size is set !
  fclose(stream);
  // printf ("the result is '%s' (%d characters)\n", buf, len);
  // free(buf);

  /* destroy all */
  myhtml_collection_destroy(collection);
  // myhtml_collection_destroy(new_collection);

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


