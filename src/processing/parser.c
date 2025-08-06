#include <stddef.h>
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
/*
static void assign_macess_and_offset(struct combo *c, struct combo_cmd *c_cmd)
{
	const size_t r_amount = c->reg_amount;
	
	const unsigned int src_op_len = c->regs_op_len[0];
	const unsigned int dst_op_len = c->regs_op_len[r_amount - 1];
}
*/

void analyze_combo(struct combo *c, struct combo_cmd *c_cmd)
{
	are_invalid_op(c);
	assign_src_and_dst_reg(c, c_cmd);
	c_cmd->act = assign_action(c);
}
