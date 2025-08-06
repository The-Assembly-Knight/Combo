#include <stdio.h>
#include <stdlib.h>

#include "../../include/errors/parsing_errors.h"

void error_invalid_op_len(void)
{
	perror("ERROR: A combo contains an invalid amount of operators");
	exit(EXIT_FAILURE);
}
