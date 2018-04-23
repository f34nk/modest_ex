#include "eterm_vec.h"

char* eterm_vec_join(vec_eterm_t* vec, const char* delimiter)
{
  if(vec == NULL) {
    return NULL;
  }

  if(vec->length == 0) {
    return NULL;
  }

  size_t len;
  char* buf = NULL;
  FILE* stream;
  stream = open_memstream(&buf, &len);

  int i;
  ETERM* term;
  eterm_vec_foreach(vec, term, i) {
    char* term_string = erl_iolist_to_string(term);
    fprintf(stream, "%.*s", (int)strlen(term_string), (char*)term_string);
    erl_free(term_string);

    if(i < vec->length - 1 && strlen(delimiter) > 0) {
      fprintf(stream, "%.*s", (int)strlen(delimiter), (char*)delimiter);
    }
  }

  fclose(stream);

  // User must free this data.
  return buf;
}

void eterm_vec_dump(vec_eterm_t* v, FILE* stream)
{
  int i;
  ETERM* term;
  eterm_vec_foreach(v, term, i) {
    erl_print_term(stream, term);
  }
  if(v->length > 0) {
    fprintf(stream, "\n");
  }
}

void eterm_dump(ETERM* term, FILE* stream)
{
  erl_print_term(stream, term);
  fprintf(stream, "\n");
}

char* eterm_to_string(ETERM* term)
{
  size_t len;
  char* buf = NULL;
  FILE* stream;
  stream = open_memstream(&buf, &len);

  erl_print_term(stream, term);

  fclose(stream);
  return buf;
}

void eterm_vec_destroy(vec_eterm_t* vec)
{
  if(vec == NULL) {
    return;
  }

  while(vec->length > 0) {
    ETERM* term = eterm_vec_pop(vec);
    erl_free_term(term); 
  }

  eterm_vec_deinit(vec);
  vec = NULL;
  erl_eterm_release();
}