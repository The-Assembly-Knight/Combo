#pragma once

#include <unistd.h>
#include <stdbool.h>

#include "../structs/combo.h"

#define REGISTER_AMOUNT  4
#define OPERATORS_AMOUNT 4

bool get_next_combo(const char *buffer);
