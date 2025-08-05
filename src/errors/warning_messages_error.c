#include <stdio.h>
#include <stdlib.h>

#include "../../include/errors/warning_messages_errors.h"

void error_writting(void)
{
	perror("Error writting warning_messages");
	exit(FAILURE_EXIT);
}
