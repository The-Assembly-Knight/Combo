#pragma once

#include "../enums/registers.h"

struct combo {
	unsigned int len;

	unsigned int reg_amount;
	
	enum reg regs[REGISTERS_AMOUNT];
	unsigned int regs_op_len[REGISTERS_AMOUNT];
	unsigned int regs_op_start_off[REGISTERS_AMOUNT];
};
