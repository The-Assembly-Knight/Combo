#pragma once

enum reg {NONE, A, B, X, Y};

struct combo {
	unsigned int len;

	unsigned int reg_amount;

	enum reg first_reg;
	enum reg second_reg;
	enum reg third_reg;
	enum reg fourth_reg;

	unsigned int first_reg_op_start_off;
	unsigned int second_reg_op_start_off;
	unsigned int third_reg_op_start_off;
};
