#pragma once

#include <stdbool.h>

#include "../enums/registers.h"
#include "../enums/actions.h"
#include "../enums/mem_access.h"

struct combo_cmd {
	enum reg src_reg;
	enum reg dst_reg;

	int src_offset;
	int dst_offset;

	enum mem_access src_mem_access;
	enum mem_access dst_mem_access;

	enum action act;
};
