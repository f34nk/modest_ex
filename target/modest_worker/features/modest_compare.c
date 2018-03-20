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

#include <cJSON/cJSON.h>
#include "utils.h"

#define DEBUG false

void add_append_instruction(cJSON *result, const char* selector, const char* html)
{
  cJSON *obj = cJSON_CreateArray();
  cJSON_AddItemToArray(obj, cJSON_CreateString("append"));
  cJSON_AddItemToArray(obj, cJSON_CreateString(selector));
  cJSON_AddItemToArray(obj, cJSON_CreateString(html));
  cJSON_AddItemToArray(result, obj);
}

void add_remove_instruction(cJSON *result, const char* selector)
{
  cJSON *obj = cJSON_CreateArray();
  cJSON_AddItemToArray(obj, cJSON_CreateString("remove"));
  cJSON_AddItemToArray(obj, cJSON_CreateString(selector));
  cJSON_AddItemToArray(result, obj);
}

bool compare_tag_names(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2)
{
  if(node1 && node2){
    const char *tag_name1 = myhtml_tag_name_by_id(node1->tree, myhtml_node_tag_id(node1), NULL);
    const char *tag_name2 = myhtml_tag_name_by_id(node2->tree, myhtml_node_tag_id(node2), NULL);
    if(strcmp(tag_name1, tag_name2) == 0){
      return true;
    }
  }
  return false;
}

bool is_text_node(myhtml_tree_node_t* node)
{
  if(node){
    const char *tag_name = myhtml_tag_name_by_id(node->tree, myhtml_node_tag_id(node), NULL);
    if(strcmp(tag_name, "-text") == 0){
      return true;
    }
  }
  return false;
}
bool do_compare_nodes(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2)
{
  if(compare_tag_names(node1, node2) == true){
    if(is_text_node(node1)){
      // compare text
      return true;
    }
    else {
      // compare attributes
      return true;
    }
  }
  return false;
}

char* remove_scope_from_selector(char* selector, const char* scope){
  if(strcmp(scope, "body_children") == 0){
    remove_substring(selector, "html ");
    remove_substring(selector, "body ");
  }
  return selector;
}

void compare_nodes(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2, int indent, const char* scope, cJSON *result)
{
  if(DEBUG){
    for(int i = 0; i < indent; i++){
      printf("\t");
    }
  }

  if(!node1 && node2) {
    // is missing in html1
    // append to html1
    myhtml_tree_node_t* parent_node2 = myhtml_node_parent(node2);
    // const char *parent_tag_name2 = myhtml_tag_name_by_id(node2->tree, myhtml_node_tag_id(parent_node2), NULL);
    
    
    char *selector = serialize_selector(parent_node2);
    remove_scope_from_selector(selector, scope);
    char *html = serialize_node(node2);
    
    if(DEBUG) printf("append '%s' to '%s'\n", html, selector);
    add_append_instruction(result, selector, html);

    free(html);
    free(selector);

    return;
  }
  else if(node1 && !node2) {
    // is missing in html2
    // remove from html1
    myhtml_tree_node_t* parent_node1 = myhtml_node_parent(node1);
    const char *parent_tag_name1 = myhtml_tag_name_by_id(node1->tree, myhtml_node_tag_id(parent_node1), NULL);
    // printf("remove '%s' from '%s' in html1\n", tag_name1, parent_tag_name1);

    char *selector = serialize_selector(node1);
    remove_scope_from_selector(selector, scope);
    char *html = serialize_node(node1);

    if(DEBUG) printf("remove '%s' at '%s'\n", html, selector);
    add_remove_instruction(result, selector);

    free(selector);
    free(html);

    return;
  }
  else if(!node1 && !node2){
    if(DEBUG) printf("NULL NULL\n");
    return;
  }
  else if(do_compare_nodes(node1, node2)){

    const char *tag_name1 = myhtml_tag_name_by_id(node1->tree, myhtml_node_tag_id(node1), NULL);
    const char *tag_name2 = myhtml_tag_name_by_id(node2->tree, myhtml_node_tag_id(node2), NULL);
    if(DEBUG) printf("\"%s\" == \"%s\"\n", tag_name1, tag_name2);
    return;
  }
  else {
    if(DEBUG) printf("Nodes are different!\n");
    return;
  }
}

void compare_trees(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2, int indent, const char* scope, cJSON *result)
{
  myhtml_tree_node_t* child_node1 = NULL;
  myhtml_tree_node_t* child_node2 = NULL;
  myhtml_tree_node_t* next_node1 = NULL;
  myhtml_tree_node_t* next_node2 = NULL;

  if(node1){
    child_node1 = myhtml_node_child(node1);
    next_node1 = myhtml_node_next(node1);
  }
  if(node2){
    child_node2 = myhtml_node_child(node2);
    next_node2 = myhtml_node_next(node2);
  }

  compare_nodes(node1, node2, indent, scope, result);

  // AND = only parse similar tree
  if(child_node1 && child_node2) {
  // OR = parse different tree
  // if(child_node1 || child_node2) {
    compare_trees(child_node1, child_node2, indent + 1, scope, result);
  }

  if(next_node1 || next_node2){
    compare_trees(next_node1, next_node2, indent, scope, result);
  }
}

/**
 * Compare two html strings.
 * @param  html1 [a html string]
 * @param  html2 [a html string]
 * @param  delimiter [a string]
 * @param  scope [scope string]
 * @return       [comparison]
 */
const char* modest_compare(const char* html1, const char* html2, const char* scope)
{
  cJSON* result = NULL;
  result = cJSON_CreateArray();

  /* init MyHTML and parse HTML */
  myhtml_tree_t *tree1 = parse_html(html1, strlen(html1));
  myhtml_tree_t *tree2 = parse_html(html2, strlen(html2));

  myhtml_tree_node_t *node1 = get_scope_node(tree1, scope);
  myhtml_tree_node_t *node2 = get_scope_node(tree2, scope);

  compare_trees(node1, node2, 0, scope, result);

  char *string = cJSON_Print(result);
  cJSON_Delete(result);

  // TODO: This is a leak. Implement proper memory handling.
  return string;
}


