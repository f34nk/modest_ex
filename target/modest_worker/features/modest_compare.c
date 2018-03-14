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
#include "vec.h"

void get_selector(myhtml_tree_t* tree, myhtml_tree_node_t* node, vec_str_t v)
{
  const char *tag_name = NULL;
  if(node){
    tag_name = myhtml_tag_name_by_id(tree, myhtml_node_tag_id(node), NULL);
    if(strcmp(tag_name, "-undef") == 0){
      // printf("\n");

      int i; char *val;
      vec_foreach_rev(&v, val, i) {
        printf("%s ", val);
      }
      // vec_foreach_ptr(&v, val, i) {
      //   printf("%s ", val);
      // }
      printf("\n");

      return;
    }
    // printf("%s", tag_name);
    vec_push(&v, concat_string(tag_name, "\0"));
    // printf("%d ", v.length);

    myhtml_tree_node_t* parent_node = myhtml_node_parent(node);
    if(parent_node){
      // printf(" ");
      get_selector(tree, parent_node, v);
    }
    else {
      // printf("\n");
    }
  }
  else {
    // printf("\n");
  }
}

void print_selector(vec_str_t v)
{
  // printf("%d\n", v.length);
  // int i; char* val;
  // vec_foreach(&v, val, i) {
  //   printf("%s ", val);
  // }
  // printf("\n");
}

void compare_nodes(myhtml_tree_t* tree1, myhtml_tree_t* tree2, myhtml_tree_node_t* node1, myhtml_tree_node_t* node2, myhtml_tree_node_t* parent_node1, myhtml_tree_node_t* parent_node2, /*myhtml_tree_node_t* prev_node1, myhtml_tree_node_t* prev_node2,*/ int indent)
{
  const char *tag_name1 = NULL;
  const char *tag_name2 = NULL;

  if(node1){
    tag_name1 = myhtml_tag_name_by_id(tree1, myhtml_node_tag_id(node1), NULL);
  }
  if(node2){
    tag_name2 = myhtml_tag_name_by_id(tree2, myhtml_node_tag_id(node2), NULL);
  }

  for(int i = 0; i < indent; i++){
    printf("\t");
  }

  /*if(!tag_name1 && parent1 && tag_name2) {
    // is missing in html1
    // append to html1
    const char *parent_tag_name1 = myhtml_tag_name_by_id(tree1, myhtml_node_tag_id(parent1), NULL);
    printf("append '%s' to '%s' in html1\n", tag_name2, parent_tag_name1);
    return;
  }
  else*/ if(!tag_name1 && !parent_node1 && parent_node2 && tag_name2) {
    // is missing in html1
    // append to html1
    const char *parent_tag_name2 = myhtml_tag_name_by_id(tree2, myhtml_node_tag_id(parent_node2), NULL);
    printf("append '%s' to '%s' in html1\n", tag_name2, parent_tag_name2);

    vec_str_t v;
    vec_init(&v);
    get_selector(tree2, node2, v);
    vec_deinit(&v);
    return;
  }
  else if(tag_name1 && parent_node1 && !tag_name2) {
    // is missing in html2
    // remove from html1
    const char *parent_tag_name1 = myhtml_tag_name_by_id(tree1, myhtml_node_tag_id(parent_node1), NULL);
    printf("remove '%s' from '%s' in html1\n", tag_name1, parent_tag_name1);

    vec_str_t v;
    vec_init(&v);
    get_selector(tree1, node1, v);
    vec_deinit(&v);
    return;
  }
  else if(!tag_name1 && !tag_name2){
    printf("NULL NULL\n");
    return;
  }
  else if(strcmp(tag_name1, tag_name2) == 0){
    printf("'%s' == '%s'\n", tag_name1, tag_name2);
    return;
  }
  else {
    printf("'%s' != '%s'\n", tag_name1, tag_name2);
    return;
  }
}

void compare_trees(myhtml_tree_t* tree1, myhtml_tree_t* tree2, myhtml_tree_node_t* node1, myhtml_tree_node_t* node2, int indent)
{
  // if(!node1 && !node2){
  //   printf("done\n");
  //   return;
  // }

  myhtml_tree_node_t* parent_node1 = NULL;
  myhtml_tree_node_t* parent_node2 = NULL;
  myhtml_tree_node_t* child_node1 = NULL;
  myhtml_tree_node_t* child_node2 = NULL;
  // myhtml_tree_node_t* prev_node1 = NULL;
  // myhtml_tree_node_t* prev_node2 = NULL;
  myhtml_tree_node_t* next_node1 = NULL;
  myhtml_tree_node_t* next_node2 = NULL;

  if(node1){
    parent_node1 = myhtml_node_parent(node1);
    child_node1 = myhtml_node_child(node1);
    next_node1 = myhtml_node_next(node1);
  }
  if(node2){
    parent_node2 = myhtml_node_parent(node2);
    child_node2 = myhtml_node_child(node2);
    next_node2 = myhtml_node_next(node2);
  }

  compare_nodes(tree1, tree2, node1, node2, parent_node1, parent_node2, indent);

  // AND = only parse similar tree
  if(child_node1 && child_node2) {
  // OR = parse different tree
  // if(child_node1 || child_node2) {
    compare_trees(tree1, tree2, child_node1, child_node2, indent + 1);
  }

  if(next_node1 || next_node2){
    compare_trees(tree1, tree2, next_node1, next_node2, indent);
  }
}

/**
 * Compare two html strings.
 * @param  html1 [a html string]
 * @param  html2 [a html string]
 * @param  scope [scope string]
 * @return       [comparison]
 */
const char* modest_compare(const char* html1, const char* html2, const char* scope)
{
  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree1 = parse_html(html1, strlen(html1));
  myhtml_tree_t *tree2 = parse_html(html2, strlen(html2));

  myhtml_tree_node_t *node1 = get_scope_node(tree1, scope);
  myhtml_tree_node_t *node2 = get_scope_node(tree2, scope);

  compare_trees(tree1, tree2, node1, node2, 0);

  return "";
}


