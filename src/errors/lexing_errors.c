#include "../../include/errors/lexing_errors.h"
#include <stdio.h>
#include <stdlib.h>

void error_op_before_first_reg(void)
{
	perror("ERROR: One or multiple operators were found before the first register of a combo");
	exit(EXIT_FAILURE);
}
