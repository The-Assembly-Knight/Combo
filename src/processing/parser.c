#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../include/processing/parser.h"
#include "../../include/errors/parsing_errors.h"

static void assign_src_and_dst_reg(struct combo *c, struct combo_cmd *c_cmd)
{
	const enum reg *regs = c->regs;
	const size_t r_amount = c->reg_amount;
	
	c_cmd->src_reg = regs[0];
	c_cmd->dst_reg = regs[r_amount - 1];
}

static enum action identify_reg_act(enum reg reg)
{
	switch (reg) {
	case A:	return ADD;
	case B: return SUBTRACT;
	case X: return MOVE;
	case Y: return SWAP;
	default: return CLEAR;
	}
}

static enum action assign_action(struct combo *c)
{
	const enum reg *regs = c->regs;
	const size_t r_amount = c->reg_amount; 
	

	switch (r_amount) {
	case 1: return CLEAR;
	case 2: return COPY;
	case 3: return identify_reg_act(regs[r_amount - 2]);
	default: return PRINT;
	}
}


static void are_invalid_op(struct combo *c)
{
	const unsigned int r_amount = c->reg_amount;
	const unsigned int *op_lens = c->regs_op_len;

	switch (r_amount) {
	case 3:
		if (op_lens[r_amount - 2] != 0)
			error_invalid_op_len();
		break;
	case 4:
		if (op_lens[r_amount - 2] != 0 || op_lens[r_amount - 3] != 0)
			error_invalid_op_len();
		break;
	}
}

static bool is_valid_arithmetic_op(const char *op, const unsigned int len)
{
	const unsigned int arithmetic_op_len = 8;

	printf("The src ops len is: %u\n", len);
	printf("The first op is %c\n", op[0]);
	

	if (len != arithmetic_op_len)
		return false;

	size_t i = 0;
	for (i = 0; i < arithmetic_op_len; i++) {
		if (op[i] != '^' && op[i] != 'v')
			return false;
	}
	
	return true;
}

static bool is_valid_memory_op(const char op, const unsigned int len)
{
	const unsigned int memory_op_len = 1;

	if (len != memory_op_len)
		return false;

	if (op != '<' && op != '>')
		return false;

	return true;
}

static unsigned int calculate_arithmetic_op_value(char *start_off)
{
	printf("REACHED");
	unsigned int total = 0;

	const unsigned int ARITHMETIC_OP_VALUE = 8;
	const unsigned int VALUES[8] = 
		{128, 64, 32, 16, 8, 4, 2, 1};

	size_t i = 0;
	for (i = 0; i < ARITHMETIC_OP_VALUE; i++) {
		if (start_off[i] == '^')
			total += VALUES[i];
	}

	return total;
}

static void assign_macess_and_offset(const unsigned int OP_LEN, char *start_off, bool *macces, unsigned int *offset)
{
	if (is_valid_memory_op(*start_off, OP_LEN))
		*macces = true;
	else if (is_valid_arithmetic_op(start_off, OP_LEN)) {
		*offset = calculate_arithmetic_op_value(start_off);
	} else
		error_invalid_op();
}

static void check_reg_ops(struct combo *c, struct combo_cmd *c_cmd, char *buffer)
{
	const unsigned int R_AMOUNT = c->reg_amount;

	const unsigned int SRC_OP_LEN = c->regs_op_len[0];
	const unsigned int DST_OP_LEN = c->regs_op_len[R_AMOUNT - 1];

	if (SRC_OP_LEN > 0) {
		char *src_start_off = buffer + c->regs_op_start_off[0] + 1;
		assign_macess_and_offset(SRC_OP_LEN, src_start_off, &c_cmd->src_macces, &c_cmd->src_offset);
	}

	if (DST_OP_LEN > 0) {
		char *dst_start_off = buffer + c->regs_op_start_off[R_AMOUNT - 1] + 2;
		assign_macess_and_offset(DST_OP_LEN, dst_start_off, &c_cmd->dst_macces, &c_cmd->dst_offset);
	}
}

void analyze_combo(struct combo *c, struct combo_cmd *c_cmd, char *buffer)
{
	are_invalid_op(c);
	assign_src_and_dst_reg(c, c_cmd);
	c_cmd->act = assign_action(c);

	check_reg_ops(c, c_cmd, buffer);
}
