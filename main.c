#include <unistd.h>
#include <stdbool.h>

#include "include/fileio/file_reading.h"
#include "include/fileio/fileio_constants.h"
#include "include/warning_messages/usage.h"
#include "include/processing/lexer.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_usage();
		return 1;
	}

	char input_buffer[MAX_AMOUNT_TO_READ + 1] = {0};
	
	read_file(argv[1], input_buffer, MAX_AMOUNT_TO_READ);

	const bool combo_found = get_next_combo(input_buffer);
	
	int ret_code = combo_found;
	
	return ret_code;
}
