
#include "test_includes.h"
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
  if (stream == NULL)
    /* handle error */ ;
    TEST_ERROR
    return 1;

  fprintf (stream, "hello my world");
  fflush (stream);
  printf ("buf=%s, len=%zu\n", buf, len);
  eob = ftello(stream);
  fseeko (stream, 0, SEEK_SET);
  fprintf (stream, "good-bye");
  fseeko (stream, eob, SEEK_SET);
  fclose (stream);
  printf ("buf=%s, len=%zu\n", buf, len);
  free (buf);

  printf("ok\n");
  return 0;
}