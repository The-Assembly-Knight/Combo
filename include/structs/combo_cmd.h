#pragma once

#include <stdbool.h>

#include "../enums/registers.h"
#include "../enums/actions.h"

struct combo_cmd {
	enum reg src_reg;
	enum reg dst_reg;

	unsigned int src_offset;
	unsigned int dst_offset;

	bool src_mem_access;
	bool dst_mem_access;

	enum action act;
};
