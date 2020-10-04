#include <assert.h>

#include "../callfull.h"

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 2
	});

	// Fills half of buffer.
	const char first[1] = {};
	callfull_feed(callfull, first, sizeof(first));

	assert(callfull_size(callfull) == 1);

	callfull_reset(callfull);

	assert(callfull_size(callfull) == 0);

	// Reaches threshold once.
	const char second[3] = {};
	callfull_feed(callfull, second, sizeof(second));

	assert(callfull_size(callfull) == 1);

	callfull_reset(callfull);

	assert(callfull_size(callfull) == 0);

	return 0;
}