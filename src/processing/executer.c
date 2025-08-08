#include <stdio.h>

#include "../../include/processing/executer.h"
#include "../../include/errors/executing_errors.h"
#include "../../include/globals/index_globals.h"

static int reg_a = 0;
static int reg_b = 0;
static int reg_x = 0;
static int reg_y = 0;

static int *src_reg = &reg_a;
static int *dst_reg = &reg_a;

#define MAX_LOOP_AMOUNT 1

static unsigned int loop_starts[MAX_LOOP_AMOUNT] = {0};
static unsigned int loops_amount = 0;

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

static void exec_print_act(void)
{
	if (reg_y > 255)
		error_printing_a_non_ASCII_value();

	printf("%c", reg_y);
}

static void exec_copy_act(void)
{
	if (*src_reg == *dst_reg)
		return;

	*dst_reg = *src_reg;
}

static void exec_loop_start(void)
{
	if (loops_amount == MAX_LOOP_AMOUNT)
		error_surpassed_max_loops_amount();
	
	loop_starts[loops_amount] = start_off;
	loops_amount++;
}

static void exec_loop_end(void)
{
	if (loops_amount == 0)
		error_subceeded_min_amount_of_loops();

	if (reg_x <= 0) {
		loop_starts[loops_amount - 1] = 0;
		loops_amount--;
		return;
	}

	start_off = loop_starts[loops_amount - 1];
	reg_x--;
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
	case PRINT:
		exec_print_act();
		break;
	case COPY:
		exec_copy_act();
		break;
	case LOOP_START:
		exec_loop_start();
		break;
	case LOOP_END:
		exec_loop_end();
		break;
	default:
		error_no_supported_action();
	}
}

void execute_c_cmd(struct combo_cmd c_cmd)
{
	if (c_cmd.act == LOOP_START || c_cmd.act == LOOP_END) {
		exec_act(c_cmd);
		return;
	}

	src_reg = assign_reg(c_cmd.src_reg);
	dst_reg = assign_reg(c_cmd.dst_reg);

	if (!assign_offsets(c_cmd.src_offset, c_cmd.dst_offset))
		error_assigning_offsets();
	
	exec_act(c_cmd);
}
