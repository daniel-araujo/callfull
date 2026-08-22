#include <assert.h>

#include "../callfull.h"

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 3
	});

	// Nothing accumulated yet.
	assert(callfull_reset(callfull) == 0);

	// Partially fills buffer.
	const char first[2] = {};
	callfull_feed(callfull, first, sizeof(first));

	assert(callfull_reset(callfull) == 2);

	// Buffer was just discarded, so it's empty again.
	assert(callfull_reset(callfull) == 0);

	return 0;
}
