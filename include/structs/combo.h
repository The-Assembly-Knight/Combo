#pragma once

#define REGISTERS_AMOUNT 4

enum reg {NONE, A, B, X, Y};

struct combo {
	unsigned int len;

	unsigned int reg_amount;
	
	enum reg regs[REGISTERS_AMOUNT];
	unsigned int regs_op_len[REGISTERS_AMOUNT];
};
