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
