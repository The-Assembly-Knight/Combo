#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "include/enums/actions.h"
#include "include/fileio/file_reading.h"
#include "include/fileio/fileio_constants.h"
#include "include/structs/combo_cmd.h"
#include "include/warning_messages/usage.h"
#include "include/processing/lexer.h"
#include "include/processing/parser.h"


int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_usage();
		return 1;
	}

	char input_buffer[MAX_AMOUNT_TO_READ + 1] = {0};
	read_file(argv[1], input_buffer, MAX_AMOUNT_TO_READ);


	struct combo combo = {
		.len = 0,
		.reg_amount = 0,
		.regs[0] = NONE,
		.regs[1] = NONE,
		.regs[2] = NONE,
		.regs[3] = NONE,
		.regs_op_len[0] = 0,
		.regs_op_len[1] = 0,
		.regs_op_len[2] = 0,
		.regs_op_len[3] = 0,
		.regs_op_start_off[0] = 0,
		.regs_op_start_off[1] = 0,
		.regs_op_start_off[2] = 0,
		.regs_op_start_off[3] = 0,
	};

	const bool combo_found = get_next_combo(input_buffer, &combo);
	
	if (!combo_found)
		return 1;
	
	struct combo_cmd combo_cmd = {
		.src_reg = NONE,
		.dst_reg = NONE,
		.src_offset = 0,
		.dst_offset = 0,
		.src_macces = false,
		.dst_macces = false,
		.act = CLEAR
	};

	analyze_combo(&combo, &combo_cmd, input_buffer);

	printf("Amount of registers: %u\n", combo.reg_amount);
	printf("First register is: %u\n", combo.regs[0]);
	printf("First operator length is: %u\n", combo.regs_op_len[0]);

	printf("The src reg is: %u\n", combo_cmd.src_reg);
	
	printf("The dst reg is: %u\n", combo_cmd.dst_reg);
	printf("The action is: %u\n", combo_cmd.act);
	
	printf("The src reg offset is: %u\n", combo_cmd.src_offset);
	printf("The src macces is: %u\n", combo_cmd.src_macces);

	printf("The dst reg offset is: %u\n", combo_cmd.dst_offset);
	printf("The dst macces is: %u\n", combo_cmd.dst_macces);
}
