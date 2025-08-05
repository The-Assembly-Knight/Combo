#include "include/fileio/file_reading.h"
#include "include/fileio/fileio_constants.h"
#include "include/warning_messages/usage.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_usage();
		return 1;
	}

	char input_buffer[MAX_AMOUNT_TO_READ + 1] = {0};
	
	read_file(argv[1], input_buffer, MAX_AMOUNT_TO_READ);

	return 0;
}
