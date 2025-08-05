#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "../../include/fileio/file_reading.h"
#include "../../include/errors/fileio_errors.h"

static bool is_invalid_ret(int ret_code)
{
	if (ret_code < 0)
		return true;

	return false;
}

static bool is_invalid_read_ret(ssize_t ret_code)
{
	if (ret_code < 0)
		return true;

	return false;
}

/*
 * Reads up to `amount_to_read` bytes from the file at `path` into `buffer`.
 * Returns the number of bytes actually read.
 * Aborts using error_*() if any step fails.
 */

ssize_t read_file(const char *path, char *buffer, const unsigned int amount_to_read)
{
	if (!path || !buffer)
		error_null_pointers();

	int fd = open(path, O_RDONLY);
	if (is_invalid_ret(fd))
		error_opening();

	ssize_t amount_read = read(fd, buffer, amount_to_read);
	if (is_invalid_read_ret(amount_read))
		error_reading();
	
	int close_ret = close(fd);
	if (is_invalid_ret(close_ret))
		error_closing();

	return amount_read;
}
