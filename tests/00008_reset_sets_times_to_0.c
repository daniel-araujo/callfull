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

	const char first[5] = {};
	callfull_feed(callfull, first, sizeof(first));

	assert(callfull_times(callfull) == 2);

	callfull_reset(callfull);

	assert(callfull_times(callfull) == 0);

	return 0;
}