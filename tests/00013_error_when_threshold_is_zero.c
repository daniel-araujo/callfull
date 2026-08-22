#include <assert.h>

#include "../callfull.h"

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 0
	});

	assert(callfull == NULL);

	assert(callfull_error(callfull) == CALLFULL_ERROR_OUT_OF_MEMORY);

	return 0;
}
