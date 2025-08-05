#include <stdbool.h>

#include "../../include/processing/lexer.h"

static unsigned int start_off = 0;

static const char valid_bytes[VALID_BYTES_AMOUNT] = {
	'A', 'B', 'X', 'Y', '<', '>', '^', 'v'
};

static bool is_byte_valid(const char byte)
{
	unsigned int i = 0;

	for (i = 0; i < VALID_BYTES_AMOUNT; i++) {
		if (valid_bytes[i] == byte)
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
