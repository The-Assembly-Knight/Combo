#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "../../include/processing/lexer.h"
#include "../../include/errors/lexing_errors.h"

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

	const size_t r_amount = combo->reg_amount;

	if (r_amount < REGISTER_AMOUNT) {
		combo->regs[r_amount] = reg_type;
		combo->reg_amount++;
		return;
	}

	error_four_plus_reg_combo();
}

static void assign_op(struct combo *combo)
{
	const size_t r_amount = combo->reg_amount;

	if (r_amount == 0)
		error_op_before_first_reg();

	if (r_amount < OPERATORS_AMOUNT)
		combo->regs_op_len[r_amount - 1]++;
	else
		error_op_after_fourth_reg();

	if (combo->regs_op_start_off[r_amount - 1] == 0)
		combo->regs_op_start_off[r_amount - 1] = start_off;
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

	/* Since the amount of registers and operators is the same use one of them */
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
		} else assign_op(combo);

		combo->len++;
		start_off++;
		byte = buffer[start_off];
	} while (is_byte_valid(byte));

	return true;
}


bool get_next_combo(const char *buffer, struct combo *c)
{
	const char byte = buffer[start_off];

	bool combo_beg_found = true;

	if (!is_byte_valid(byte))
		combo_beg_found = find_combo_beg(buffer);

	if (!combo_beg_found)
		return false; 

	find_combo_end(buffer, c);

	return true;
}
