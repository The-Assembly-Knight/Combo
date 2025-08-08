#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../include/processing/parser.h"
#include "../../include/errors/parsing_errors.h"

#define ARITH_OP_LEN	8
#define MEM_OP_LEN	1
static const int ARITH_WEIGHTS[ARITH_OP_LEN] = {
	128, 64, 32, 16, 8, 4, 2, 1
};

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

static enum action determine_action_based_on_combo(struct combo *c)
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


static void validate_intermediate_register_ops(const struct combo *c)
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

static bool is_valid_memory_op(const char op, const unsigned int len, enum mem_access *mem_access)
{
	if (len != MEM_OP_LEN)
		return false;
	
	switch (op) {
	case '<': 
		*mem_access = ADDRESS;
		break;
	case '>': 
		*mem_access = DEREFERENCE;
		break;
	default: return false;
	}

	return true;
}

static bool parse_arithmetic_op(const char *op, const unsigned int len, int *offset)
{
	if (len != ARITH_OP_LEN) return false;

	int total = 0;

	size_t i = 0;
	for (i = 0; i < ARITH_OP_LEN; i++) {
		const char c = op[i];

		if (c != '^' && c != 'v') return false;
		if (c == '^') total += ARITH_WEIGHTS[i];
	}
	*offset = total;
	return true;
}

static void assign_mem_access_and_offset(const unsigned int op_len, const char *start_off, enum mem_access *mem_access, int *offset)
{
	if (is_valid_memory_op(*start_off, op_len, mem_access))
		return;
	else if (parse_arithmetic_op(start_off, op_len, offset))
		return;
	else
		error_invalid_op();
}

static void check_reg_ops(const struct combo *c, struct combo_cmd *c_cmd, char *buffer)
{
	const unsigned int r_amount = c->reg_amount;

	const unsigned int SRC_OP_LEN = c->regs_op_len[0];
	const unsigned int DST_OP_LEN = c->regs_op_len[r_amount - 1];

	if (SRC_OP_LEN > 0) {
		char *src_start_off = buffer + c->regs_op_start_off[0];
		assign_mem_access_and_offset(SRC_OP_LEN, src_start_off, &c_cmd->src_mem_access, &c_cmd->src_offset);
	}

	if (DST_OP_LEN > 0 && r_amount != 1) {
		char *dst_start_off = buffer + c->regs_op_start_off[r_amount - 1];
		assign_mem_access_and_offset(DST_OP_LEN, dst_start_off, &c_cmd->dst_mem_access, &c_cmd->dst_offset);
	}
}

void analyze_combo(struct combo *c, struct combo_cmd *c_cmd, char *buffer)
{
	validate_intermediate_register_ops(c);
	assign_src_and_dst_reg(c, c_cmd);
	c_cmd->act = determine_action_based_on_combo(c);

	check_reg_ops(c, c_cmd, buffer);
}
