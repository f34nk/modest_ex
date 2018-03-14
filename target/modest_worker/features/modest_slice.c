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
#include "modest_slice.h"

// const char* get_scoped_selector_for_slice(const char* selector, const char* scope){
//   if(strcmp(scope, "html") == 0){
//     return get_concat_string("html, html ", selector);
//   }
//   else if(strcmp(scope, "head") == 0){
//     return get_concat_string("head, head ", selector);
//   }
//   else if(strcmp(scope, "body") == 0){
//     return get_concat_string("body, html ", get_concat_string(selector, " :not(head)"));
//   }
//   else if(strcmp(scope, "body_children") == 0){
//     return get_concat_string("body ", selector);
//   }
//   else if(strcmp(scope, "form") == 0){
//     return get_concat_string("form, ", selector);
//   }
//   // default
//   return selector;
// }

myhtml_collection_t* slice(myhtml_t *myhtml, myhtml_collection_t *collection, int start, int end)
{
  if(collection && collection->list && collection->length){

    if(end == -1) {
      end = collection->length;
    }

    if(start >= 0 && end >= 0) {

      int new_collection_size = end - start;
      // printf("new_collection_size %d\n", new_collection_size);

      mystatus_t status;
      myhtml_collection_t *new_collection = myhtml_collection_create(new_collection_size, &status);

      for(size_t i = 0; i < start; i++) {
        myhtml_tree_node_t *node = collection->list[i];
        if(node){
          myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);
          const char *tag_name = myhtml_tag_name_by_id(node->tree, tag_id, NULL);
          // printf("exclude %d, tag_name %s\n", i, tag_name);
        }
      }
      for(size_t i = start; i < end; i++) {
        myhtml_tree_node_t *node = collection->list[i];
        if(node){
          myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);
          const char *tag_name = myhtml_tag_name_by_id(node->tree, tag_id, NULL);
          // printf("include %d, tag_name %s\n", i, tag_name);

          if(myhtml_collection_check_size(new_collection, 1, 1024) == MyHTML_STATUS_OK) {
            new_collection->list[new_collection->length] = node;
            new_collection->length++;
          }
        }
      }
      for(size_t i = end; i < collection->length; i++) {
        myhtml_tree_node_t *node = collection->list[i];
        if(node){
          myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);
          const char *tag_name = myhtml_tag_name_by_id(node->tree, tag_id, NULL);
          // printf("exclude %d, tag_name %s\n", i, tag_name);
        }
      }

      return new_collection;
    }
  }

  return NULL;
}

/**
 * Slice selected set into subset. Index each element in the set. 
 * Return a set from start to end.
 * @param  html      [a html string]
 * @param  selector  [a CSS selector]
 * @param  start     [start index]
 * @param  end       [end index]
 * @param  delimiter [delimiter string]
 * @param  scope     [scope string]
 * @return           [delimited string]
 */
const char* modest_slice_selected(const char* html, const char* selector, int start, int end, const char* delimiter, const char* scope)
{
  // const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  // const char *selector = "div > :nth-child(2n+1):not(:has(a))";

  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree = parse_html(html, strlen(html));

  /* create css parser and finder for selectors */
  mycss_entry_t *css_entry = create_css_parser();
  modest_finder_t *finder = modest_finder_create_simple();

  const char* new_selector = get_scoped_selector(selector, scope);
  // printf("scoped_selector: %s\n", new_selector);

  /* parse selectors */
  mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, new_selector, strlen(new_selector));

  /* find nodes by selector */
  myhtml_collection_t *collection = NULL;
  // modest_finder_by_selectors_list(finder, get_scope_node(tree, scope), selectors_list, &collection);
  modest_finder_by_selectors_list(finder, tree->node_html, selectors_list, &collection);

  // /* print found result */
  // printf("\n\nFound nodes:");
  // open the stream
  FILE *stream;
  char *buf;
  size_t len;
  stream = open_memstream(&buf, &len);

  myhtml_collection_t *new_collection = slice(tree->myhtml, collection, start, end);

  print_found_result(tree, new_collection, delimiter, stream);

  // close the stream, the buffer is allocated and the size is set !
  fclose(stream);
  // printf ("the result is '%s' (%d characters)\n", buf, len);
  // free(buf);

  /* destroy all */
  myhtml_collection_destroy(collection);
  myhtml_collection_destroy(new_collection);

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


