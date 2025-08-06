#include "../../include/errors/lexing_errors.h"
#include <stdio.h>
#include <stdlib.h>

void error_op_before_first_reg(void)
{
	perror("ERROR: One or multiple operators were found before the first register of a combo");
	exit(EXIT_FAILURE);
}

void error_four_plus_reg_combo(void)
{
	perror("ERROR: A combo contains an excess of registers");
	exit(EXIT_FAILURE);
}
