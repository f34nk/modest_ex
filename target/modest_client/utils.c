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

#define DIE(msg, ...) do { fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#define CHECK_STATUS(msg, ...) do {if(status) DIE(msg, ##__VA_ARGS__);} while(0)

mystatus_t serialization_bad_selectors(const char* buffer, size_t size, void* ctx)
{
  printf("%.*s", (int)size, buffer);
  return MyCORE_STATUS_OK;
}

/**
 * Parse html string into a tree structure.
 * @param  data      [a html string]
 * @param  data_size [size of the html string]
 * @return           [a html tree]
 */
myhtml_tree_t * parse_html(const char* data, size_t data_size)
{
  myhtml_t* myhtml = myhtml_create();
  mystatus_t status = myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

  CHECK_STATUS("Can't init MyHTML object\n");

  myhtml_tree_t* tree = myhtml_tree_create();
  status = myhtml_tree_init(tree, myhtml);

  CHECK_STATUS("Can't init MyHTML Tree object\n");

  status = myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
  CHECK_STATUS("Can't parse HTML:\n%s\n", data);

  return tree;
}

mycss_entry_t * create_css_parser(void)
{
  // base init
  mycss_t *mycss = mycss_create();
  mystatus_t status = mycss_init(mycss);

  CHECK_STATUS("Can't init MyCSS object\n");

  // currenr entry work init
  mycss_entry_t *entry = mycss_entry_create();
  status = mycss_entry_init(mycss, entry);

  CHECK_STATUS("Can't init MyCSS Entry object\n");

  return entry;
}

mycss_selectors_list_t * prepare_selector(mycss_entry_t *css_entry, const char* selector, size_t selector_size)
{
  mystatus_t out_status;
  mycss_selectors_list_t *list = mycss_selectors_parse(mycss_entry_selectors(css_entry),
                             MyENCODING_UTF_8,
                             selector, selector_size,
                             &out_status);
  /* check parsing errors */
  if(list == NULL || (list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)) {
    fprintf(stderr, "Bad CSS Selectors\n");

    if(list) {
      mycss_selectors_serialization_list(mycss_entry_selectors(css_entry), list,
                         serialization_bad_selectors, NULL);
      printf("\n");
    }

    exit(EXIT_FAILURE);
  }

  return list;
}

mystatus_t serialization_callback(const char* data, size_t len, FILE *stream)
{
  fprintf(stream, "%.*s", (int)len, data);
  return MyCORE_STATUS_OK;
}

void print_found_result(myhtml_tree_t* html_tree, myhtml_collection_t *collection, const char* delimiter, FILE *stream)
{
  if(collection) {
    // fprintf(stream, "(");
    for(size_t i = 0; i < collection->length; i++) {
      // myhtml_serialization_node_callback(collection->list[i], serialization_callback, stream);
      myhtml_serialization_tree_callback(collection->list[i], serialization_callback, stream);
      if(i < collection->length - 1){
        fprintf(stream, delimiter);
      }
    }
    // fprintf(stream, ")");
    // fprintf(stream, "\n");
  }
  else {
    fprintf(stream, "");
  }
}

/**
 *  Write output
 *  @param  buffer
 *  @param  size
 *  @param  ptr
 */
mystatus_t write_output(const char* data, size_t len, void* ctx)
{
  fprintf(ctx, "%.*s", (int)len, data);
  return MyCORE_STATUS_OK;
}