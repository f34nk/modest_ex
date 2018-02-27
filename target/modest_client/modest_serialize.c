
#include <stdio.h>
#include <stdlib.h>
#include <myhtml/api.h>

const char* modest_serialize(const char* html){
  // basic init
  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

  // init tree
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);

  // parse html
  myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

  mycore_string_raw_t str_raw;
  mycore_string_raw_clean_all(&str_raw);

  if(myhtml_serialization_tree_buffer(myhtml_tree_get_document(tree), &str_raw)) {
    fprintf(stderr, "Could not serialization for the tree\n");
    return "";
  }

  // printf("%s", str_raw.data);
  // mycore_string_raw_destroy(&str_raw, false);

  // release resources
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);

  return str_raw.data;
}