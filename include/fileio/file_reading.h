#pragma once

#include <unistd.h>

ssize_t read_file(const char *path, char *buffer, const unsigned int amount_to_read);
