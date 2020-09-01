#include <assert.h>

#include "../callfull.h"

static int called = 0;

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
	assert(i == called);
	called += 1;
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 2
	});

	// Calls once.
	const char first[2] = {};
	callfull_feed(callfull, first, sizeof(first));
	assert(called == 1);

	// Calls twice.
	const char second[4] = {};
	callfull_feed(callfull, second, sizeof(second));
	assert(called == 3);

	return 0;
}