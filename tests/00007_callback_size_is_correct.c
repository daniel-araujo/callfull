#include <assert.h>

#include "../callfull.h"

static int called = 0;

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
	assert(size == 2);
	called += 1;
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 2
	});

	// Filled exact size.
	const char first[2] = {};
	callfull_feed(callfull, first, sizeof(first));
	assert(called == 1);

	// Filled current buffer and half of the next buffer.
	const char second[3] = {};
	callfull_feed(callfull, second, sizeof(second));
	assert(called == 2);

	// Finished filling current buffer.
	const char third[1] = {};
	callfull_feed(callfull, third, sizeof(third));
	assert(called == 3);

	return 0;
}