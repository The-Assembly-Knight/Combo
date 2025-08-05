#include <stdbool.h>

#include "../../include/processing/lexer.h"

static unsigned int start_off = 0;

static const char reg_bytes[REGISTER_AMOUNT] = {
	'A', 'B', 'X', 'Y'
};

static const char op_bytes[OPERATORS_AMOUNT] = {
	'<', '>', '^', 'v'
};

static enum reg identify_reg(const char reg)
{
	switch (reg) {
	case 'A': return A;
	case 'B': return B;
	case 'X': return X;
	case 'Y': return Y;
	default:  return NONE;
	}
}

static void assign_reg(const enum reg reg_type, struct combo *combo)
{
	size_t i = 0;

	for (i = 0; i < REGISTER_AMOUNT; i++) {
		if (combo->regs[i] == NONE) {
			combo->regs[i] = reg_type;
			break;
		}
	}
	
	combo->reg_amount++;
}

static bool is_byte_register(const char byte)
{
	size_t i = 0;

	for (i = 0; i < REGISTER_AMOUNT; i++) {
		if (reg_bytes[i] == byte)
			return true;
	}

	return false;
}

static bool is_byte_valid(const char byte)
{
	size_t i = 0;

	for (i = 0; i < REGISTER_AMOUNT; i++) {
		if (reg_bytes[i] == byte || op_bytes[i] == byte)
			return true;
	}

	return false;
}

static bool find_combo_beg(const char *buffer)
{
	char byte = buffer[start_off];

	do {
		start_off++;
		byte = buffer[start_off];
	} while (!is_byte_valid(byte) && byte != '\0');

	if (byte == '\0')
		return false;

	return true;
}

static bool find_combo_end(const char *buffer, struct combo *combo)
{
	char byte = buffer[start_off];

	do {
		if (is_byte_register(byte) == 1) {
			enum reg reg_type = identify_reg(byte);
			assign_reg(reg_type, combo);
		}

		combo->len++;
		start_off++;
		byte = buffer[start_off];
	} while (is_byte_valid(byte));

	return true;
}


bool get_next_combo(const char *buffer)
{
	/* TODO: gotta use bytes_read*/

	struct combo combo = {
		.len = 0,
		.reg_amount = 0,
		.regs[0] = NONE,
		.regs[1] = NONE,
		.regs[2] = NONE,
		.regs[3] = NONE,
		.regs_op_start_off[0] = 0,
		.regs_op_start_off[1] = 0,
		.regs_op_start_off[2] = 0,
		.regs_op_start_off[3] = 0,
	};

	const char byte = buffer[start_off];

	bool combo_beg_found = true;

	if (!is_byte_valid(byte))
		combo_beg_found = find_combo_beg(buffer);

	if (!combo_beg_found)
		return false; 
	/* TODO: Make it return unsigned int to check if the combo was lexed if not then stop*/

	find_combo_end(buffer, &combo);

	return true;
}
