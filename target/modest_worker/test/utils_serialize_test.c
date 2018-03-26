
#include <myhtml/myhtml.h>
#include <modest/finder/finder.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>
#include "utils.h"

myhtml_tree_t *tree = NULL;
mycss_entry_t *css_entry = NULL;
modest_finder_t *finder = NULL;
mycss_selectors_list_t *selectors_list = NULL;

void setup(const char* html)
{
  /* init MyHTML and parse HTML */
  tree = parse_html(html, strlen(html));

  /* create css parser and finder for selectors */
  css_entry = create_css_parser();
  finder = modest_finder_create_simple();
}

void cleanup()
{
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
}

int main(int argc, const char * argv[])
{

  const char *html = "<html><head></head><body><h1>Hello</h1><p>Lorem <a>ipsum</a></p><p>dolor sit amet</p></body></html>";
  const char *selector = "a,p:last-of-type";

  setup(html);

  myhtml_collection_t *collection = NULL;
  /* parse selectors */
  selectors_list = prepare_selector(css_entry, selector, strlen(selector));
  /* find nodes by selector */
  modest_finder_by_selectors_list(finder, tree->node_html, selectors_list, &collection);

  if(!collection || collection->length == 0) return 1;

  myhtml_tree_node_t *node = collection->list[0];
  const char* result = serialize_node(node);
  printf("1: %s\n", result);
  if(strcmp(result, "<a>ipsum</a>") != 0){
    printf("Failed\n");
    /* destroy all */
    myhtml_collection_destroy(collection);
    collection = NULL;
    cleanup();
    return 1;
  }

  result = serialize_selector(node);
  printf("2: %s\n", result);
  if(strcmp(result, "html body p a") != 0){
    printf("Failed\n");
    /* destroy all */
    myhtml_collection_destroy(collection);
    collection = NULL;
    cleanup();
    return 1;
  }

  node = collection->list[1];
  result = serialize_node(node);
  printf("3: %s\n", result);
  if(strcmp(result, "<p>dolor sit amet</p>") != 0){
    printf("Failed\n");
    /* destroy all */
    myhtml_collection_destroy(collection);
    collection = NULL;
    cleanup();
    return 1;
  }

  result = serialize_selector(node);
  printf("4: %s\n", result);
  if(strcmp(result, "html body p") != 0){
    printf("Failed\n");
    /* destroy all */
    myhtml_collection_destroy(collection);
    collection = NULL;
    cleanup();
    return 1;
  }
  /* destroy all */
  myhtml_collection_destroy(collection);
  collection = NULL;

  cleanup();
  return 0;
}