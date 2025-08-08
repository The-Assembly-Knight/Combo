#include <stdlib.h>
#include <stdio.h>

#include "../../include/processing/executer.h"
#include "../../include/errors/executing_errors.h"

static int reg_a = 0;
static int reg_b = 0;
static int reg_x = 0;
static int reg_y = 0;

static int *src_reg = &reg_a;
static int *dst_reg = &reg_a;

static int* assign_reg(enum reg reg)
{
	int* ret_reg = &reg_a;
	switch (reg) {
	case A:
		ret_reg = &reg_a;
		break;
	case B:
		ret_reg = &reg_b;
		break;
	case X:
		ret_reg = &reg_x;
		break;
	case Y:
		ret_reg = &reg_y;
		break;
	default:
		error_invalid_register_found();
	}
	return ret_reg;
}

static bool assign_offsets(const int src_offset, const int dst_offset)
{
	if (src_reg == NULL || dst_reg == NULL)
		return false;
	
	*src_reg += src_offset;
	*dst_reg += dst_offset;

	return true;
}

static void exec_clear_act(const int src_offset)
{
	if (src_offset != 0)
		return;

	*src_reg = 0;
}

static void exec_move_act(void)
{
	if (src_reg == dst_reg)
		error_moving_register_to_itself();

	*dst_reg = *src_reg;
	*src_reg = 0;
}

static void exec_swap_act(void)
{
	if (*src_reg == *dst_reg)
		return;

	int tmp = *src_reg;
	*src_reg = *dst_reg;
	*dst_reg = tmp;
}

static void exec_add_act(void)
{
	if (*src_reg == 0)
		return;

	*dst_reg += *src_reg;
}

static void exec_subtract_act(void)
{
	if (*src_reg == 0)
		return;

	*dst_reg -= *src_reg;
}

static void exec_act(const struct combo_cmd c_cmd)
{
	switch (c_cmd.act) {
	case CLEAR: 
		exec_clear_act(c_cmd.src_offset);
		break;
	case MOVE:
		exec_move_act();
		break;
	case SWAP:
		exec_swap_act();
		break;
	case ADD:
		exec_add_act();
		break;
	case SUBTRACT:
		exec_subtract_act();
		break;
	default:
		error_no_supported_action();
	}
}

void execute_c_cmd(struct combo_cmd c_cmd)
{
	src_reg = assign_reg(c_cmd.src_reg);
	dst_reg = assign_reg(c_cmd.dst_reg);

	if (!assign_offsets(c_cmd.src_offset, c_cmd.dst_offset))
		error_assigning_offsets();
	
	exec_act(c_cmd);


	printf("This is the value of the register A: %i\n", reg_a);
	printf("This is the value of the register B: %i\n", reg_b);
}
