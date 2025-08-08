#include <stdio.h>
#include <stdlib.h>

#include "../../include/errors/lexing_errors.h"

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

void error_op_after_fourth_reg(void)
{
	perror("ERROR: A combo containts operators after its fourth register");
	exit(EXIT_FAILURE);
}

void error_loop_has_no_end(void)
{
	perror("ERROR: Loop starts but not ends, please make sure the loop has an ending ('>')");
	exit(EXIT_FAILURE);
}
