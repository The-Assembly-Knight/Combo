#include <stdio.h>
#include <stdlib.h>

#include "../../include/errors/executing_errors.h"

void error_invalid_register_found(void)
{
	perror("ERROR: Invalid register was found in a combo");
	exit(EXIT_FAILURE);
}
