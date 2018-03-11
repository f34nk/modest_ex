/*
 Copyright (C) 2015-2016 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <myhtml/api.h>

/* Format */
#ifdef _WIN32
    #define MyCORE_FMT_Z "%Iu"
#else
    #define MyCORE_FMT_Z "%zu"
#endif

// #include "example.h"

struct res_html {
  char  *html;
  size_t size;
};

// struct res_html load_html_file(const char* filename)
// {
//   FILE *fh = fopen(filename, "rb");
//   if(fh == NULL) {
//     fprintf(stderr, "Can't open html file: %s\n", filename);
//     exit(EXIT_FAILURE);
//   }
  
//   if(fseek(fh, 0L, SEEK_END) != 0) {
//     fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
//     exit(EXIT_FAILURE);
//   }
  
//   long size = ftell(fh);
  
//   if(fseek(fh, 0L, SEEK_SET) != 0) {
//     fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
//     exit(EXIT_FAILURE);
//   }
  
//   if(size <= 0) {
//     fprintf(stderr, "Can't get file size or file is empty: %s\n", filename);
//     exit(EXIT_FAILURE);
//   }
  
//   char *html = (char*)malloc(size + 1);
//   if(html == NULL) {
//     fprintf(stderr, "Can't allocate mem for html file: %s\n", filename);
//     exit(EXIT_FAILURE);
//   }
  
//   size_t nread = fread(html, 1, size, fh);
//   if (nread != size) {
//     fprintf(stderr, "could not read %ld bytes (" MyCORE_FMT_Z " bytes done)\n", size, nread);
//     exit(EXIT_FAILURE);
//   }

//   fclose(fh);
  
//   struct res_html res = {html, (size_t)size};
//   return res;
// }

void colorize_print(mycore_incoming_buffer_t *inc_buf, size_t begin, size_t length, const char* color, FILE *stream)
{
  if(length) {
    inc_buf = mycore_incoming_buffer_find_by_position(inc_buf, begin);
    
    size_t between_begin  = (begin - mycore_incoming_buffer_offset(inc_buf));
    const char* between_data = mycore_incoming_buffer_data(inc_buf);
    
    fprintf(stream, "%s%.*s\e[0m", color, (int)length, &between_data[between_begin]);
  }
}

size_t colorize_print_attributes(myhtml_tree_t* tree, myhtml_tree_attr_t* attr, mycore_incoming_buffer_t *inc_buf, size_t last_pos, FILE *stream)
{
  while(attr)
  {
    myhtml_position_t key_pos = myhtml_attribute_key_raw_position(attr);
    myhtml_position_t value_pos = myhtml_attribute_value_raw_position(attr);
    
    if(key_pos.length)
    {
      /* print <div[ ]key=value> */
      if(last_pos < key_pos.begin)
        colorize_print(inc_buf, last_pos, (key_pos.begin - last_pos), "\e[31m", stream);
      
      /* print <div [key]=value> */
      colorize_print(inc_buf, key_pos.begin, key_pos.length, "\e[33m", stream);
      
      /* get/check max position */
      if((key_pos.begin + key_pos.length) > last_pos)
        last_pos = key_pos.begin + key_pos.length;
    }
    else {
      /* print <div[ ]value> */
      if(value_pos.length && last_pos < value_pos.begin)
        colorize_print(inc_buf, last_pos, (value_pos.begin - last_pos), "\e[31m", stream);
    }
    
    if(value_pos.length)
    {
      /* print <div key[=]value> */
      if(key_pos.length) {
        size_t between_begin = key_pos.begin + key_pos.length;
        colorize_print(inc_buf, between_begin, (value_pos.begin - between_begin), "\e[31m", stream);
      }
      
      /* print <div key=[value]> */
      colorize_print(inc_buf, value_pos.begin, value_pos.length, "\e[34m", stream);
      
      /* get/check max position */
      if(value_pos.begin + value_pos.length > last_pos)
        last_pos = value_pos.begin + value_pos.length;
    }
    
    attr = myhtml_attribute_next(attr);
  }
  
  return last_pos;
}

void * colorize_callback_before_token_done(myhtml_tree_t* tree, myhtml_token_node_t* token, FILE *stream)
{
  mycore_incoming_buffer_t *inc_buf = myhtml_tree_incoming_buffer_first(tree);
  
  myhtml_position_t token_pos = myhtml_token_node_raw_position(token);
  myhtml_position_t token_element_pos = myhtml_token_node_element_position(token);
  
  size_t last_pos = token_pos.begin + token_pos.length;
  
  switch (myhtml_token_node_tag_id(token)) {
    case MyHTML_TAG__DOCTYPE: {
      /* print [<!DOCTYPE] */
      colorize_print(inc_buf, token_element_pos.begin, (token_pos.begin - token_element_pos.begin), "\e[37m", stream);
      
      colorize_print(inc_buf, token_pos.begin, token_pos.length, "\e[37m", stream);
      
      /* print [>] */
      colorize_print(inc_buf, last_pos, ((token_element_pos.begin + token_element_pos.length) - last_pos), "\e[37m", stream);
      break;
    }
    case MyHTML_TAG__TEXT: {
      colorize_print(inc_buf, token_pos.begin, token_pos.length, "\e[0m", stream);
      break;
    }
    case MyHTML_TAG__COMMENT: {
      /* print [<!--] */
      colorize_print(inc_buf, token_element_pos.begin, (token_pos.begin - token_element_pos.begin), "\e[32m",stream);
      
      colorize_print(inc_buf, token_pos.begin, token_pos.length, "\e[32m", stream);
      
      /* print [-->] */
      colorize_print(inc_buf, last_pos, ((token_element_pos.begin + token_element_pos.length) - last_pos), "\e[32m", stream);
      break;
    }
    default: {
      /* print [<]div> */
      colorize_print(inc_buf, token_element_pos.begin, (token_pos.begin - token_element_pos.begin), "\e[31m", stream);
      
      /* print <[div]> */
      colorize_print(inc_buf, token_pos.begin, token_pos.length, "\e[31m", stream);
      
      if(myhtml_token_node_attribute_first(token))
        last_pos = colorize_print_attributes(tree, myhtml_token_node_attribute_first(token), inc_buf, last_pos, stream);
      
      /* print <div[>] */
      colorize_print(inc_buf, last_pos, ((token_element_pos.begin + token_element_pos.length) - last_pos), "\e[31m", stream);
      
      break;
    }
  }
  
  return stream;
}

/**
 * Pretty print html to device.
 * @param  html   [a html string]
 * @param  device [device name]
 * @return        [updated html string]
 */
const char* modest_pretty_print(const char* html)
{   
  // struct res_html res = load_html_file(path);
  struct res_html res = {html, strlen(html)};

  // basic init
  myhtml_t* myhtml = myhtml_create();
  myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
  
  // init tree
  myhtml_tree_t* tree = myhtml_tree_create();
  myhtml_tree_init(tree, myhtml);
  
  // open the stream
  FILE *stream;
  char *buf;
  size_t len;
  stream = open_memstream(&buf, &len);

  myhtml_callback_before_token_done_set(tree, colorize_callback_before_token_done, stream);
  
  // parse html
  myhtml_parse(tree, MyENCODING_UTF_8, res.html, res.size);
  
  fprintf(stream, "\n");
  
  // close the stream, the buffer is allocated and the size is set !
  fclose(stream);
  // printf ("the result is '%s' (%d characters)\n", buf, len);
  // free(buf);
  
  myhtml_tree_destroy(tree);
  myhtml_destroy(myhtml);
  
  // free(res.html);
  
  // TODO: This is a leak. Implement proper memory handling.
  return buf;
}
