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
#include "vec.h"
#include "utils.h"

#define DEBUG true

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

void add_set_text_instruction(cJSON *result, const char* selector, const char* new_text)
{
  cJSON *obj = cJSON_CreateArray();
  cJSON_AddItemToArray(obj, cJSON_CreateString("set_text"));
  cJSON_AddItemToArray(obj, cJSON_CreateString(selector));
  cJSON_AddItemToArray(obj, cJSON_CreateString(new_text));
  cJSON_AddItemToArray(result, obj);
}

void add_set_attribute_instruction(cJSON *result, const char* selector, const char* key, const char* value)
{
  cJSON *obj = cJSON_CreateArray();
  cJSON_AddItemToArray(obj, cJSON_CreateString("set_attribute"));
  cJSON_AddItemToArray(obj, cJSON_CreateString(selector));
  cJSON_AddItemToArray(obj, cJSON_CreateString(key));
  cJSON_AddItemToArray(obj, cJSON_CreateString(value));
  cJSON_AddItemToArray(result, obj);
}

void add_set_tag_instruction(cJSON *result, const char* selector, const char* new_tag)
{
  cJSON *obj = cJSON_CreateArray();
  cJSON_AddItemToArray(obj, cJSON_CreateString("set_tag"));
  cJSON_AddItemToArray(obj, cJSON_CreateString(selector));
  cJSON_AddItemToArray(obj, cJSON_CreateString(new_tag));
  cJSON_AddItemToArray(result, obj);
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

bool has_attributes(myhtml_tree_node_t* node)
{
  if(node){
    myhtml_tree_attr_t *attr = myhtml_node_attribute_first(node);
    return (attr) ? true : false;
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

bool compare_text(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2)
{
  if(node1 && node2){
    mycore_string_t *string1 = myhtml_node_string(node1);
    mycore_string_t *string2 = myhtml_node_string(node2);
    char *data1 = mycore_string_data(string1);
    char *data2 = mycore_string_data(string2);
    if(strcmp(data1, data2) == 0){
      return true;
    }
  }
  return false; 
}

vec_str_t get_attributes(myhtml_tree_node_t* node)
{
  vec_str_t v;
  vec_init(&v);

  if(node) {
    myhtml_tree_attr_t *attr = myhtml_node_attribute_first(node);
    if(attr){

      while (attr) {
        char *name = myhtml_attribute_key(attr, NULL);
        if(name) {
          // printf("%s = ", name);
          char *value = myhtml_attribute_value(attr, NULL);
          if(value){
            // printf("%s", value);
            char *buf = concat_string(name, "=");
            buf = concat_string(buf, value);
            // printf("%s\n", buf);
            vec_push(&v, buf);
          }
          // printf("\n");
        }
        attr = myhtml_attribute_next(attr);
      } // while attr

    } // if attr
  }
  return v;
}

bool compare_attributes(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2, const char* scope, cJSON *result)
{
  vec_str_t v1 = get_attributes(node1);
  vec_str_t v2 = get_attributes(node2);
  char *selector = serialize_selector(node1);
  remove_scope_from_selector(selector, scope);

  bool flag = true;
  if(v1.length == 0 && v2.length == 0){
    flag = true;
  }
  else if(v1.length == v2.length){
    for(int i = 0; i < v1.length; i++){
      char *val1 = v1.data[i];
      char *val2 = v2.data[i];
      if(strcmp(val1, val2) != 0){
        char** kv = split_string(val2, '=');
        if(DEBUG) printf("set_attribute '%s' to '%s'\n", val2, selector);
        add_set_attribute_instruction(result, selector, kv[0], kv[1]);
        free(kv);
        flag = false;
      }
    }
  }
  else if(v1.length > v2.length){
    for(int i = 0; i < v1.length; i++){
      if(i >= v2.length){
        char *val1 = v1.data[i];
        char** kv = split_string(val1, '=');
        if(DEBUG) printf("set_attribute '%s = NULL' to '%s'\n", kv[0], selector);
        add_set_attribute_instruction(result, selector, kv[0], "");
        free(kv);
        flag = false;
      }
    }
  }
  else if(v1.length < v2.length){
    for(int i = 0; i < v2.length; i++){
      if(i >= v1.length){
        char *val2 = v2.data[i];
        char** kv = split_string(val2, '=');
        if(DEBUG) printf("set_attribute '%s' to '%s'\n", val2, selector);
        add_set_attribute_instruction(result, selector, kv[0], kv[1]);
        free(kv);
        flag = false;
      }
    }
  }
  vec_deinit(&v1);
  vec_deinit(&v2);
  return flag;
}

void compare_nodes(myhtml_tree_node_t* node1, myhtml_tree_node_t* node2, int indent, const char* scope, cJSON *result)
{
  if(DEBUG){
    for(int i = 0; i < indent; i++){
      printf(".");
    }
  }

  if(!node1 && node2) {
    // is missing in html1
    // append to html1
    myhtml_tree_node_t* parent_node2 = myhtml_node_parent(node2);
    // const char *parent_tag_name2 = myhtml_tag_name_by_id(node2->tree, myhtml_node_tag_id(parent_node2), NULL);
    
    
    char *selector2 = serialize_selector(parent_node2);
    remove_scope_from_selector(selector2, scope);
    char *html = serialize_node(node2);
    
    if(DEBUG) printf("append '%s' to '%s'\n", html, selector2);
    add_append_instruction(result, selector2, html);

    free(html);
    free(selector2);
  }
  else if(node1 && !node2) {
    // is missing in html2
    // remove from html1
    myhtml_tree_node_t* parent_node1 = myhtml_node_parent(node1);
    const char *parent_tag_name1 = myhtml_tag_name_by_id(node1->tree, myhtml_node_tag_id(parent_node1), NULL);
    // printf("remove '%s' from '%s' in html1\n", tag_name1, parent_tag_name1);

    char *selector1 = serialize_selector(node1);
    remove_scope_from_selector(selector1, scope);
    char *html = serialize_node(node1);

    if(DEBUG) printf("remove '%s' at '%s'\n", html, selector1);
    add_remove_instruction(result, selector1);

    free(selector1);
    free(html);
  }
  else if(!node1 && !node2){
    if(DEBUG) printf("NULL NULL\n");
  }
  else {
    if(compare_tag_names(node1, node2) == true){
      if(is_text_node(node1) && is_text_node(node2)){
        if(compare_text(node1, node2) == false){

          myhtml_tree_node_t* parent_node1 = myhtml_node_parent(node1);
          char *selector1 = serialize_selector(parent_node1);
          remove_scope_from_selector(selector1, scope);

          myhtml_tree_node_t* parent_node2 = myhtml_node_parent(node2);
          char *selector2 = serialize_selector(parent_node2);
          remove_scope_from_selector(selector2, scope);

          mycore_string_t *string2 = myhtml_node_string(node2);
          char *data2 = mycore_string_data(string2);
          if(DEBUG) printf("set_text '%s' to '%s'\n", data2, selector2);          
          add_set_text_instruction(result, selector2, data2);

          free(selector1);
          free(selector2);
        }
      }
      else if (compare_attributes(node1, node2, scope, result) == true) {
        const char *tag_name1 = myhtml_tag_name_by_id(node1->tree, myhtml_node_tag_id(node1), NULL);
        const char *tag_name2 = myhtml_tag_name_by_id(node2->tree, myhtml_node_tag_id(node2), NULL);
        if(DEBUG) printf("'%s' == '%s'\n", tag_name1, tag_name2);
      }
    }
    else {
      char *selector1 = serialize_selector(node1);
      remove_scope_from_selector(selector1, scope);
      // char *selector2 = serialize_selector(node2);
      // remove_scope_from_selector(selector2, scope);
      const char *tag_name2 = myhtml_tag_name_by_id(node2->tree, myhtml_node_tag_id(node2), NULL);
      if(DEBUG) printf("set_tag '%s' for '%s'\n", tag_name2, selector1);
      add_set_tag_instruction(result, selector1, tag_name2);

      free(selector1);
      // free(selector2);
    }
  } // else
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

  if(child_node1 && child_node2) {
  // if(child_node1 || child_node2) {
    compare_trees(child_node1, child_node2, indent + 1, scope, result);
  }

  if(next_node1 || next_node2){
    compare_trees(next_node1, next_node2, indent, scope, result);
  }
}

myhtml_tree_node_t *get_compare_scope_node(myhtml_tree_t* tree, const char* scope){
  if(strcmp(scope, "html") == 0){
    return tree->node_html;
  }
  else if(strcmp(scope, "head") == 0){
    return tree->node_head;
  }
  else if(strcmp(scope, "body") == 0){
    return tree->node_body;
  }
  else if(strcmp(scope, "body_children") == 0){
    return myhtml_node_child(tree->node_body);
    // return tree->node_body;
  }
  else if(strcmp(scope, "form") == 0){
    return tree->node_form;
  }
  // default
  return tree->node_html;
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

  myhtml_tree_node_t *node1 = get_compare_scope_node(tree1, scope);
  myhtml_tree_node_t *node2 = get_compare_scope_node(tree2, scope);

  compare_trees(node1, node2, 0, scope, result);

  char *string = cJSON_Print(result);
  cJSON_Delete(result);

  // TODO: This is a leak. Implement proper memory handling.
  return string;
}


