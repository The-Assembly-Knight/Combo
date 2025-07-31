#include "include/file_io.h"
#include "include/globals.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: combo <file_path>\n");
    return -1;
  }
  
  read_file(argv[1], input_file_buffer, MAX_FILE_SIZE);

  return 0;
}
