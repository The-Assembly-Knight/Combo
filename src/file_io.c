#include "../include/file_io.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

ssize_t read_file(const char *path, char *out_buf, size_t max_size) {
  int fd = open(path, O_RDONLY);

  if (fd < 0) {return -1;}
  
  ssize_t n = read(fd, out_buf, max_size);
  close(fd);
  return n;
}
