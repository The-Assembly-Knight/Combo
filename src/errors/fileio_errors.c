#include "../../include/errors/fileio_errors.h"
#include <stdio.h>
#include <stdlib.h>

void error_null_pointers(void)
{
	perror("Error path or buffer are null pointers");
	exit(EXIT_FAILURE);
}

void error_opening(void)
{
	perror("Error opening file\n");
	exit(EXIT_FAILURE);
}

void error_reading(void)
{
	perror("Error reading from file\n");
	exit(EXIT_FAILURE);
}

void error_closing(void)
{
	perror("Error closing file\n");
	exit(EXIT_FAILURE);
}
