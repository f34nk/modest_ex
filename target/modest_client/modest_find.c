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
#include "modest_find.h"

/**
 * Find nodes with a CSS selector with optional delimiter.
 * @param  html      [a html string]
 * @param  selector  [a CSS selector]
 * @param  delimiter [a delimiter string]
 * @return           [a html string]
 */
const char* modest_find(const char* html, const char* selector, const char* delimiter, const char* scope)
{
  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree = parse_html(html, strlen(html));

  /* create css parser and finder for selectors */
  mycss_entry_t *css_entry = create_css_parser();
  modest_finder_t *finder = modest_finder_create_simple();

  const char* new_selector = get_scoped_selector(selector, scope);
  printf("scoped_selector: %s\n", new_selector);

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

  print_found_result(tree, collection, delimiter, stream);

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
  return buf;
}


