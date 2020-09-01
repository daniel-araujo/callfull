#include <assert.h>

#include "../callfull.h"

static int called = 0;

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
	called += 1;
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 2
	});

	// Does not hit threshold.
	const char first[1] = {};
	callfull_feed(callfull, first, sizeof(first));

	assert(called == 0);

	// Hits threshold.
	const char second[1] = {};
	callfull_feed(callfull, second, sizeof(second));

	assert(called == 1);

	// Hits threshold again.
	const char third[2] = {};
	callfull_feed(callfull, third, sizeof(third));

	assert(called == 2);

	// Hits threshold twice.
	const char fourth[4] = {};
	callfull_feed(callfull, fourth, sizeof(fourth));

	assert(called == 4);

	return 0;
}