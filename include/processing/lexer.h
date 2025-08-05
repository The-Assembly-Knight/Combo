#pragma once

#include <unistd.h>
#include <stdbool.h>

#include "../structs/combo.h"

#define VALID_BYTES_AMOUNT 8

bool get_next_combo(const char *buffer);
