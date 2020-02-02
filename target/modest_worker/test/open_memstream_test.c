
#include "test_includes.h"
#include "open_memstream.h"
/*
To check for memory leaks execute test with term_arrayalgrind.

  valgrind --leak-check=yes target/modest_worker/build/test/open_memstream_test

*/
int main(int argc, const char* argterm_array[])
{

  FILE *stream;
  char *buf;
  size_t len;
  off_t eob;

  stream = open_memstream (&buf, &len);
  if (stream == NULL) {
    TEST_ERROR
    printf("\tFunction open_memstream returned NULL.\n");
    return 1;
  }

  fprintf (stream, "world");
  fflush (stream);
  printf("-> buf=%s, len=%zu\n", buf, len);
  if(strcmp(buf, "world") != 0 && len == 5) {
    free (buf);
    TEST_ERROR
    return 1;
  }

  eob = ftello(stream);
  fseeko (stream, 0, SEEK_SET);
  fprintf (stream, "hello ");
  fseeko (stream, eob, SEEK_SET);
  fclose (stream);
  printf("-> buf=%s, len=%zu\n", buf, len);
  if(strcmp(buf, "hello world") != 0 && len == 11) {
    free (buf);
    TEST_ERROR
    return 1;
  }

  free (buf);

  printf("ok\n");
  return 0;
}