#include <unistd.h>
#include <sys/types.h>

#include "../../include/warning_messages/usage.h"
#include "../../include/errors/warning_messages_errors.h"

void print_usage(void)
{
	static const char message[] = "Usage ./combo <file_name>\n";
	const ssize_t write_ret = write(STDOUT_FILENO, message, sizeof(message) - 1);

	if (write_ret < 0)
		error_writting();
}
