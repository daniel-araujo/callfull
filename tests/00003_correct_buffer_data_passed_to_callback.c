#include <assert.h>

#include "../callfull.h"

// Using this counter to track whether callback receives correct data.
static int counter = 0;

static void callback(const char *buffer, size_t size, size_t i, void *user)
{
	for (size_t i = 0; i < size; i++) {
		assert(buffer[i] == counter);
		counter += 1;
	}
}

int main(int argc, char *argv[])
{
	callfull_t callfull = callfull_create(&(struct callfull_opts) {
		.callback = callback,

		.threshold = 2
	});

	// Hits threshold with no leftover.
	const char first[2] = { 0, 1 };
	callfull_feed(callfull, first, sizeof(first));

	// Hits threshold with leftover.
	const char second[3] = { 2, 3, 4 };
	callfull_feed(callfull, second, sizeof(second));

	// Completes current buffer and hits threshold with leftover.
	const char third[2] = { 5, 6 };
	callfull_feed(callfull, third, sizeof(third));

	// Completes current buffer.
	const char fourth[1] = { 7 };
	callfull_feed(callfull, fourth, sizeof(fourth));

	return 0;
}