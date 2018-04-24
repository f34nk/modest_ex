#ifndef TEST_UTILS_H
#define TEST_UTILS_H

char* read_file(const char* filename)
{
  FILE* file = fopen(filename, "rb");
  if(file == NULL) {
    fprintf(stderr, "Failed to open file '%s'\n", filename);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  if(filesize == (int)0) {
    fprintf(stderr, "Failed to tell filesize for file '%s'\n", filename);
    fclose(file);
    return NULL;
  }
  fseek(file, 0, SEEK_SET);  //same as rewind(f);
  // rewind(file);

  char* string = malloc(filesize + 1);
  if(string == NULL) {
    fprintf(stderr, "Failed to malloc string with size %d for file '%s'\n", (int)filesize, filename);
    fclose(file);
    return NULL;
  }
  size_t readsize = fread(string, 1, filesize, file);
  if((int)readsize != (int)filesize) {
    fprintf(stderr, "Failed to read string with size %d for file '%s'\n", (int)filesize, filename);
    fclose(file);
    return NULL;
  }

  fclose(file);

  string[filesize] = 0;

  return string;
}

void write_file(const char* filepath, const char* data)
{
  FILE* file = fopen(filepath, "ab");
  if (file != NULL) {
    fputs(data, file);
    fclose(file);
  }
}

#endif