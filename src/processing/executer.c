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
	int* ret_reg;

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

void execute_c_cmd(struct combo_cmd c_cmd)
{
	src_reg = assign_reg(c_cmd.src_reg);
	dst_reg = assign_reg(c_cmd.dst_reg);
}

