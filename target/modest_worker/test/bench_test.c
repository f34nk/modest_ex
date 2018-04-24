#include <time.h>

// #include "modest_html.h"
#include "test_includes.h"
#include "test_utils.h"
/*
To check for memory leaks execute test with valgrind.

  valgrind --leak-check=yes test/bench_test
*/

#define CLOCK_LOG fprintf(stdout, "[LOG]\t%s()\n", __func__);
#define CLOCK_LOG_ERROR fprintf(stderr, "[ERROR]\t%s()\n\t%s:%d\n", __func__, __FILE__, __LINE__);

// const char* filename = "../test/fixtures/0_2k.html";
// const char* filename = "../test/fixtures/0_5k.html";
// const char* filename = "../test/fixtures/1k.html";
const char* filename = "../test/fixtures/2k.html";

int handle_serialize_bench(int c, const char* html)
{
  if(c == 0) {
    CLOCK_LOG
  }

  html_workspace_t* w = html_init();

  // const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
  const char *scope = "html";
  vec_eterm_t term_array;
  eterm_vec_init(&term_array);
  serialize(w, html, scope, &term_array);
  char* result = eterm_vec_join(&term_array, "|");
  // printf("-> %s\n", result);
  // if(strcmp(result, "<html><head></head><body><div><p id=\"p1\"></p><p id=\"p2\"></p><p id=\"p3\"><a>link</a></p><p id=\"p4\"></p><p id=\"p5\"></p><p id=\"p6\"></p></div></body></html>") != 0){
  //   eterm_vec_destroy(&term_array);
  //   free(result);
  //   html_destroy(w);
  //   TEST_ERROR
  //   return 1;
  // }
  eterm_vec_destroy(&term_array);
  free(result);

  html_destroy(w);

  return 0;
}

#define clock_to_sec(t) ((double)t)/CLOCKS_PER_SEC
#define clock_to_milisec(t) (((double)t)/CLOCKS_PER_SEC) * 1000.0
#define clock_to_microsec(t) (((double)t)/CLOCKS_PER_SEC) * 1000.0 * 1000

#define max_benchmarks 1
int (*bench[max_benchmarks])() = {handle_serialize_bench};

int main(int argc, char* argv[])
{
  char* html = read_file(filename);
  if(html == NULL) {
    return 1;
  }

  // initialize all of Erl_Interface
  erl_init(NULL, 0);

  int i = 0;
  int result = 0;
  while(i < max_benchmarks && result == 0) {
    clock_t start = clock();
    clock_t diff = clock() - start;
    int c = 0;
    while(clock_to_sec(diff) < 1.0 && result == 0) {
      result = bench[i](c, html);
      diff = clock() - start;
      c += 1;
    }
    clock_t end = clock() - start;
    double average = clock_to_sec(end) / c;
    // average = average * 1000.0; // millisec
    average = average * 1000.0 * 1000.0; // microsec
    printf("\trun %d times\ttotal %2.4f sec\taverage = %f µs\n", c, (float)clock_to_sec(end), average);
    i += 1;
  }

  // µ

  free(html);
  return 0;
}