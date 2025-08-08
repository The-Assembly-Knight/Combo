#include <stdio.h>
#include <stdlib.h>

#include "../../include/errors/executing_errors.h"

void error_invalid_register_found(void)
{
	perror("ERROR: Invalid register was found in a combo");
	exit(EXIT_FAILURE);
}

void error_assigning_offsets(void)
{
	perror("ERROR: src_reg pointer or dst_reg pointer pointed to NULL");
	exit(EXIT_FAILURE);
}

void error_no_supported_action(void)
{
	perror("ERROR: action not supported yet");
	exit(EXIT_FAILURE);
}

void error_offset_is_negative(void)
{
	perror("ERROR: an offset is negative");
	exit(EXIT_FAILURE);
}

void error_moving_register_to_itself(void)
{
	perror("ERROR: a combo moves a register to itself, you can not move a register to itself");
	exit(EXIT_FAILURE);
}

void error_printing_a_non_ASCII_value(void)
{
	perror("ERROR: trying to print a value greater than 255, not an ASCII character");
	exit(EXIT_FAILURE);
}
